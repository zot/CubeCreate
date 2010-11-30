/* Copyright 2010 q66 <quaker66@gmail.com>
 * 
 * The file is part of CubeCreate project, which is licensed under MIT license.
 * The license file should be bundled with your CubeCreate distribution.
 * 
 */

// SEE THE HEADER FOR GENERAL DOCUMENTATION

/////////////////////
// ENGINE INCLUDES //
/////////////////////

#include "cube.h"
#include "engine.h"
#include "game.h"

/////////////////////////
// CUBECREATE INCLUDES //
/////////////////////////

#include "world_system.h"
#include "message_system.h"
#include "utility.h"
#include "fpsclient_interface.h"
#ifdef CLIENT
    #include "client_system.h"
    #include "targeting.h"
#endif

// actually create the pointers
#include "engine_variables_registers.h"

///////////////////////////
// ENGINE VARIABLE CLASS //
///////////////////////////

/*
 * PUBLICS
 */

/*
 * Constructors
 */

// this one is used for any type of integer variables. Arguments "cb" and "persist" are optional.
EngineVariable::EngineVariable
(const std::string& vname, int minvi, int curvi, int maxvi, void (_cb_ cb)(int, int, int, int), bool persist, bool override)
{
	name = vname;
	if (minvi > maxvi)
	{
		readOnly = true;
		minv = maxvi; curv = curvi; maxv = minvi; prev = curvi;
	}
	else
	{
		readOnly = false;
		minv = minvi; curv = curvi; maxv = maxvi; prev = curvi;
	}
	intCB = cb;
	persistent = persist;
	type = cb ? ( persist ? "IVARFP" : "IVARF" ) : ( persist ? "IVARP" : "IVAR" );
	hasCB = cb ? true : false;
}

// this one is used for double variables. Arguments cb and persist are also optional.
EngineVariable::EngineVariable
(const std::string& vname, double minvf, double curvf, double maxvf, void (_cb_ cb)(double, double, double, double), bool persist, bool override)
{
	name = vname;
	if (minvf > maxvf)
	{
		readOnly = true;
		minv = maxvf; curv = curvf; maxv = minvf; prev = curvf;
	}
	else
	{
		readOnly = false;
		minv = minvf; curv = curvf; maxv = maxvf; prev = curvf;
	}
	doubleCB = cb;
	persistent = persist;
	type = cb ? ( persist ? "FVARFP" : "FVARF" ) : ( persist ? "FVARP" : "FVAR" );
	hasCB = cb ? true : false;
}

// string variables. cb and persist are optional
EngineVariable::EngineVariable
(const std::string& vname, const std::string& curvs, void (_cb_ cb)(const std::string&, const std::string&), bool persist, bool override)
{
	name = vname;
	readOnly = false;
	curv = curvs; prev = curvs;
	stringCB = cb;
	persistent = persist;
	type = cb ? ( persist ? "SVARFP" : "SVARF" ) : ( persist ? "SVARP" : "SVAR" );
	hasCB = cb ? true : false;
}

/*
 * Getters
 */

std::string EngineVariable::getName()    { return name;  }
std::string EngineVariable::getType()    { return type;  }
int         EngineVariable::getInteger() { return anyint(curv);  }
double      EngineVariable::getDouble()  { return anydouble(curv); }
std::string EngineVariable::getString()  { return anystring(curv); }

/*
 * Setters
 */

// you use this one for integer variables; checking for right value is done in both here and lua to save stack manipulation
void EngineVariable::set(int val, bool luaSync, bool forceCB, bool clamp)
{
	prev = curv;
	if (clamp && (val < anyint(minv) || val > anyint(maxv))) curv = clamp(val, anyint(minv), anyint(maxv));
	else curv = val;
	callCB(luaSync, forceCB);
}

// float variables
void EngineVariable::set(double val, bool luaSync, bool forceCB, bool clamp)
{
	prev = curv;
	if (clamp && (val < anydouble(minv) || val > anydouble(maxv))) curv = clamp(val, anydouble(minv), anydouble(maxv));
	else curv = val;
	callCB(luaSync, forceCB);
}

// string variables
void EngineVariable::set(std::string val, bool luaSync, bool forceCB, _UNUSED_ bool dummy) // EEEEEK HACK DETECTED, find a better way! lazy coder
{
	prev = curv;
	curv = val;
	callCB(luaSync, forceCB);
}

// check if variable is persistent, publicly available
bool EngineVariable::isPersistent()
{
	return persistent;
}

// check if it's read only
bool EngineVariable::isReadOnly()
{
	return readOnly;
}

// check if it's overridable
bool EngineVariable::isOverridable()
{
	return override;
}

// these are used for registration of Lua variables after one is registered in C++
void EngineVariable::registerLuaIVAR()
{
	LuaEngine::getGlobal("ivar");
	LuaEngine::pushValue(name);
	LuaEngine::pushValue(anyint(minv));
	LuaEngine::pushValue(anyint(curv));
	LuaEngine::pushValue(anyint(maxv));
	LuaEngine::pushValue(readOnly);
	LuaEngine::call(5, 0);
}

void EngineVariable::registerLuaFVAR()
{
	LuaEngine::getGlobal("fvar");
	LuaEngine::pushValue(name);
	LuaEngine::pushValue(anydouble(minv));
	LuaEngine::pushValue(anydouble(curv));
	LuaEngine::pushValue(anydouble(maxv));
	LuaEngine::pushValue(readOnly);
	LuaEngine::call(5, 0);
}

void EngineVariable::registerLuaSVAR()
{
	LuaEngine::getGlobal("svar");
	LuaEngine::pushValue(name);
	LuaEngine::pushValue(anystring(curv));
	LuaEngine::pushValue(readOnly);
	LuaEngine::call(3, 0);
}

/*
 * PRIVATES
 */

// this one can call a callback if set; it also does a value sync with Lua which can call lua callback.
void EngineVariable::callCB(bool luaSync, bool forceCB)
{
	#define SYNCV(val) \
	if (luaSync || LuaEngine::exists()) \
	{ \
		LuaEngine::getGlobal("EV"); \
		LuaEngine::setTable(name + "_ns", val); \
		LuaEngine::pop(1); \
	}

	switch (type[0])
	{
		case 'I':
		{
			if (hasCB && (!luaSync || forceCB)) intCB(anyint(minv), anyint(maxv), anyint(prev), anyint(curv));
			SYNCV(anyint(curv));
			break;
		}
		case 'F':
		{
			if (hasCB && (!luaSync || forceCB)) doubleCB(anydouble(minv), anydouble(maxv), anydouble(prev), anydouble(curv));
			SYNCV(anydouble(curv));
			break;
		}
		case 'S':
		{
			if (hasCB && (!luaSync || forceCB)) stringCB(anystring(prev), anystring(curv));
			SYNCV(anystring(curv));
			break;
		}
		default: break;
	}
}

///////////////////////////////////
// ENGINE VARIABLE STORAGE CLASS //
///////////////////////////////////

/*
 * PRIVATES
 */

// storage for vars - used most of time
EVMap EngineVariables::storage;
// here, non-overridable variables are moved on clear, then re-used on next initialization
EVMap EngineVariables::persistentStorage;

/*
 * PUBLICS
 */

// register EngineVariablePtr into storage; doesn't call callbacks or set values or anything.
// won't register a variable that is already registered. (but won't fail either)
void EngineVariables::reg(const std::string& name, EngineVariablePtr var)
{
	if (storage.find(name) != storage.end()) return;
	storage.insert(EVPair(name, var));
}

// lets the storage fill from the other map and do new registrations into map.
void EngineVariables::fill()
{
	fillFromPersistent();
	#define _RV REGVAR
	#undef REGVAR
	#define REGVAR(name, ...) EngineVariables::reg(#name, _EV_##name)
	#define _EV_NODEF
	#include "engine_variables_registers.h"
	#undef _EV_NODEF
	#undef REGVAR
	#define REGVAR _RV
	#undef _RV
}

// takes storage map and registers those in lua
void EngineVariables::fillLua()
{
	for (EVMap::iterator it = storage.begin(); it != storage.end(); it++)
	{
		switch (it->second.get()->getType()[0])
		{
			case 'I':
			{
				it->second.get()->registerLuaIVAR();
				break;
			}
			case 'F':
			{
				it->second.get()->registerLuaFVAR();
				break;
			}
			case 'S':
			{
				it->second.get()->registerLuaSVAR();
				break;
			}
			default: break;
		}
	}
}

// clears the storage, but keeps non-overridable variables in persistentStorage
void EngineVariables::clear()
{
	for (EVMap::iterator it = storage.begin(); it != storage.end(); it++)
		if (!it->second.get()->isOverridable())
			persistentStorage.insert(*it);

	storage.clear();
}

// fills empty storage from persistentStorage, does simple assignment.
// used on script engine reinitialization to reset overridable vars
void EngineVariables::fillFromPersistent()
{
	storage = persistentStorage;
	persistentStorage.clear();
}

// those are called from Lua and take care of syncing Lua values into C++
void EngineVariables::syncFromLua(const std::string& name, int value)
{
	storage[name].get()->set(value, false);
}

void EngineVariables::syncFromLua(const std::string& name, double value)
{
	storage[name].get()->set(value, false);
}

void EngineVariables::syncFromLua(const std::string& name, const std::string& value)
{
	storage[name].get()->set(value, false);
}

// this one gets the EngineVariablePtr from storage assuming you know its name.
// Then you can get, set etc, things done with shared ptr are reflected in storage too
EngineVariablePtr& EngineVariables::get(const std::string& name)
{
	return storage[name];
}
