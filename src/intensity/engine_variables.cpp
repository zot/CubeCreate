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
#include "fpsclient_interface.h"
#ifdef CLIENT
    #include "client_system.h"
    #include "targeting.h"
#endif

// declare the pointers
#define _EV_NODEF
#include "engine_variables_registers.h"
#undef _EV_NODEF

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
(const std::string& vname, int minvi, int curvi, int maxvi, void (_cb_ cb)(int, int, int, int), bool persist, bool overridable)
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
    override = overridable;
    alias = false;
}

// this one is used for float variables. Arguments cb and persist are also optional.
EngineVariable::EngineVariable
(const std::string& vname, float minvf, float curvf, float maxvf, void (_cb_ cb)(float, float, float, float), bool persist, bool overridable)
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
    floatCB = cb;
    persistent = persist;
    type = cb ? ( persist ? "FVARFP" : "FVARF" ) : ( persist ? "FVARP" : "FVAR" );
    hasCB = cb ? true : false;
    override = overridable;
    alias = false;
}

// string variables. cb and persist are optional
EngineVariable::EngineVariable
(const std::string& vname, const std::string& curvs, void (_cb_ cb)(const std::string&, const std::string&), bool persist, bool overridable)
{
    name = vname;
    readOnly = false;
    curv = curvs; prev = curvs;
    stringCB = cb;
    persistent = persist;
    type = cb ? ( persist ? "SVARFP" : "SVARF" ) : ( persist ? "SVARP" : "SVAR" );
    hasCB = cb ? true : false;
    override = overridable;
    alias = false;
}

// integer alias
EngineVariable::EngineVariable(const std::string& aname, int val, bool alias)
{
    name = aname;
    readOnly = false;
    minv = -1; maxv = -1; prev = val; curv = val;
    floatCB = NULL;
    persistent = false;
    hasCB = false;
    type = "IVAR";
    alias = true;
    override = false;
    if (lua::engine.hashandle()) registerLuaIVAR();
}

// float alias
EngineVariable::EngineVariable(const std::string& aname, float val, bool alias)
{
    name = aname;
    readOnly = false;
    minv = -1.0f; maxv = -1.0f; prev = val; curv = val;
    floatCB = NULL;
    persistent = false;
    hasCB = false;
    type = "FVAR";
    alias = true;
    override = false;
    if (lua::engine.hashandle()) registerLuaFVAR();
}

// string alias
EngineVariable::EngineVariable(const std::string& aname, const std::string& val, bool alias)
{
    name = aname;
    readOnly = false;
    curv = val; prev = val;
    stringCB = NULL;
    persistent = false;
    hasCB = false;
    type = "SVAR";
    alias = true;
    override = false;
    if (lua::engine.hashandle()) registerLuaSVAR();
}

/*
 * Getters
 */

std::string EngineVariable::getName()    { return name;  }
std::string EngineVariable::getType()    { return type;  }
int         EngineVariable::getInteger() { return anyint(curv);  }
float       EngineVariable::getFloat()  { return anyfloat(curv); }
std::string EngineVariable::getString()  { return anystring(curv); }

/*
 * Setters
 */

// you use this one for integer variables; checking for right value is done in both here and lua to save stack manipulation
void EngineVariable::set(int val, bool luaSync, bool forceCB, bool clamp)
{
    prev = curv;
    if (clamp && (val < anyint(minv) || val > anyint(maxv)) && !alias) curv = clamp(val, anyint(minv), anyint(maxv));
    else curv = val;
    callCB(luaSync, forceCB);
}

// float variables
void EngineVariable::set(float val, bool luaSync, bool forceCB, bool clamp)
{
    prev = curv;
    if (clamp && (val < anyfloat(minv) || val > anyfloat(maxv)) && !alias) curv = clamp(val, anyfloat(minv), anyfloat(maxv));
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

// check if it's alias
bool EngineVariable::isAlias()
{
    return alias;
}

// these are used for registration of Lua variables after one is registered in C++
void EngineVariable::registerLuaIVAR()
{
    lua::engine.getg("ivar")
        .push(name.c_str())
        .push(anyint(minv))
        .push(anyint(curv))
        .push(anyint(maxv))
        .push(readOnly)
        .push(alias)
        .call(6, 0);
}

void EngineVariable::registerLuaFVAR()
{
    lua::engine.getg("fvar")
        .push(name.c_str())
        .push(anyfloat(minv))
        .push(anyfloat(curv))
        .push(anyfloat(maxv))
        .push(readOnly)
        .push(alias)
        .call(6, 0);
}

void EngineVariable::registerLuaSVAR()
{
    lua::engine.getg("svar")
        .push(name.c_str())
        .push(anystring(curv).c_str())
        .push(readOnly)
        .push(alias)
        .call(4, 0);
}

/*
 * PRIVATES
 */

// this one can call a callback if set; it also does a value sync with Lua which can call lua callback.
void EngineVariable::callCB(bool luaSync, bool forceCB)
{
    #define SYNCV(val) \
    if ((luaSync || alias) && lua::engine.hashandle()) \
    { \
        defformatstring(n)("%s_ns", name.c_str()); \
        lua::engine.getg("EV").t_set(n, val).pop(1); \
    }

    switch (type[0])
    {
        case 'I':
        {
            if (hasCB && (!luaSync || forceCB) && !alias) intCB(anyint(minv), anyint(maxv), anyint(prev), anyint(curv));
            SYNCV(anyint(curv));
            break;
        }
        case 'F':
        {
            if (hasCB && (!luaSync || forceCB) && !alias) floatCB(anyfloat(minv), anyfloat(maxv), anyfloat(prev), anyfloat(curv));
            SYNCV(anyfloat(curv));
            break;
        }
        case 'S':
        {
            if (hasCB && (!luaSync || forceCB) && !alias) stringCB(anystring(prev), anystring(curv));
            SYNCV(anystring(curv).c_str());
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

// register EngineVariable pointer into storage; doesn't call callbacks or set values or anything.
// won't register a variable that is already registered. (but won't fail either)
EngineVariable *EngineVariables::reg(const std::string& name, EngineVariable *var)
{
    if (storage.find(name) != storage.end()) return storage[name];
    storage.insert(EVPair(name, var));
    return var;
}

// lets the storage fill from the other map and do new registrations into map.
void EngineVariables::fill()
{
    fillFromPersistent();
    #define _RV REGVAR
    #undef REGVAR
    #define REGVAR(name, ...) _EV_##name = EngineVariables::reg(#name, new EngineVariable(#name, __VA_ARGS__))
    #include "engine_variables_registers.h"
    #undef REGVAR
    #define REGVAR _RV
    #undef _RV
}

// takes storage map and registers those in lua
void EngineVariables::fillLua()
{
    for (EVMap::iterator it = storage.begin(); it != storage.end(); it++)
    {
        switch (it->second->getType()[0])
        {
            case 'I':
            {
                it->second->registerLuaIVAR();
                break;
            }
            case 'F':
            {
                it->second->registerLuaFVAR();
                break;
            }
            case 'S':
            {
                it->second->registerLuaSVAR();
                break;
            }
            default: break;
        }
    }
}

// clears the storage, but keeps non-overridable variables and aliases in persistentStorage
void EngineVariables::clear()
{
    for (EVMap::iterator it = storage.begin(); it != storage.end(); it++)
        if (it->second->isAlias() || !it->second->isOverridable())
            persistentStorage.insert(*it);
        else
            delete it->second; // delete it if it shouldn't go into persistent storage and thus free the memory

    storage.clear();
}

// frees all pointers in storage
void EngineVariables::flush()
{
    for (EVMap::iterator it = persistentStorage.begin(); it != persistentStorage.end(); it++) // make sure the persistent storage is clear too
        delete it->second;

    for (EVMap::iterator it = storage.begin(); it != storage.end(); it++)
        delete it->second;

    persistentStorage.clear();
    storage.clear();
}

// fills empty storage from persistentStorage, does simple assignment.
// used on script engine reinitialization to reset overridable vars
void EngineVariables::fillFromPersistent()
{
    for (EVMap::iterator it = persistentStorage.begin(); it != persistentStorage.end(); it++)
    {
        storage.insert(*it);
    }
    persistentStorage.clear();
}

// those are called from Lua and take care of syncing Lua values into C++
void EngineVariables::syncFromLua(const std::string& name, int value)
{
    storage[name]->set(value, false);
}

void EngineVariables::syncFromLua(const std::string& name, float value)
{
    storage[name]->set(value, false);
}

void EngineVariables::syncFromLua(const std::string& name, const std::string& value)
{
    storage[name]->set(value, false);
}

// this one gets the EngineVariable pointer from storage assuming you know its name.
// Then you can get, set etc, things done with shared ptr are reflected in storage too
EngineVariable *EngineVariables::get(const std::string& name)
{
    if (storage.find(name) != storage.end()) return storage[name];
    else return NULL;
}

// when set to true, variables are always taken as persistent, when false, they never persist (not written to file)
bool EngineVariables::persistVars = false;
// when set to true, variables are always taken as overridable
bool EngineVariables::overrideVars = false;
