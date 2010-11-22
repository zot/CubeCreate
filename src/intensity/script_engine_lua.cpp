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

/////////////////////////////
// SCRIPT ENGINE EMBEDDING //
/////////////////////////////

#include "script_engine_lua_embedding.h"

///////////////////////
// PRIVATE VARIABLES //
///////////////////////

std::string LuaEngine::scriptDir = "src/lua/";
std::string LuaEngine::version   = "0.0";
bool        LuaEngine::hasState  = false;
lua_State  *LuaEngine::L         = NULL;
bool        LuaEngine::runTests  = false; // later set (when setting up embedding)
bool        LuaEngine::ranTests  = false;

/////////////////////
// PRIVATE METHODS //
/////////////////////

void LuaEngine::initLibs()
{
    if (!exists()) return;

    luaopen_base(L);
    luaopen_table(L);
    luaopen_string(L);
    luaopen_math(L);

    // hacky way to make luaopen_package work, when it doesn't itself.
    lua_pushcfunction(L, luaopen_package);
    lua_call(L, 0, 0);
}

void LuaEngine::setupModule(std::string file, bool noTests)
{
    runFile(scriptDir + file + ".lua");
    if (runTests && !noTests) runFile(scriptDir + file + "__test.lua");
}

void LuaEngine::setupEmbedding()
{
    if (!exists()) return;

    Logging::log(Logging::DEBUG, "Setting up embedding");

    runTests = Utility::Config::getInt("Logging", "scripting_tests", 1);

    if (runTests) runFile(scriptDir + "__TestingEnvironment.lua");
    if (ranTests) runTests = false;

    // setup logging outside CAPI, into its own "namespace".
    // the "namespace" is actually left on stack.
    luaL_register(L, "Logging", (luaL_Reg[]){ { "log", __script__log }, { "echo", __script__echo }, { 0, 0 } });

    // now we push logging levels, and pop the table finally
    #define PUSHLEVEL(level) setTable(#level, Logging::level);
    PUSHLEVEL(INFO)
    PUSHLEVEL(DEBUG)
    PUSHLEVEL(WARNING)
    PUSHLEVEL(ERROR)
    pop(1);

    // General modules, not relating directly to CubeCreate.
    setupModule("LoggingExtras");
    setupModule("Class");
    setupModule("JSON");
    setupModule("Signals");

    // CubeCreate modules.
    // Before setting up actual CAPI, set Global.CLIENT/SERVER right.
    setupModule("engine/Platform");
    #ifdef CLIENT
        runScript("Global:initAsClient()");
    #else // SERVER
        runScript("Global:initAsServer()");
    #endif

    // Set version to Global after CAPI is set
    getGlobal("Global");
    setTable("version", version);
    pop(1);

    // the "stubs" for registration - basically array of luaL_regs
    #include "script_engine_lua_embedding_stubs.h"
    luaL_register(L, "CAPI", CAPI);
    pop(1);

    setupModule("LuaExtensions", true); // set up lua extensions right after we have CAPI
    setupModule("engine/EngineVariables");
    setupModule("engine/CAPIExtras", true);
    setupModule("engine/Utilities");
    setupModule("engine/Actions");
    setupModule("engine/LogicEntityStore");
    setupModule("engine/Variables");
    setupModule("engine/LogicEntity");
    setupModule("engine/MessageSystem");
    setupModule("engine/LogicEntityClasses");
    setupModule("engine/ModelAttachments");
    setupModule("engine/Animatable");
    setupModule("engine/Character");
    setupModule("engine/StaticEntity");
    setupModule("engine/Sound");
    setupModule("engine/Application");
    setupModule("engine/Effects");

    // If tests were run, restart the engine after running them. Mainly to make sure everything is back as needed
    if (runTests)
    {
        destroy();
        ranTests = true;
        create();
    }
}

//////////////////////////////
// PUBLIC VARIABLES/METHODS //
//////////////////////////////

std::map<std::string, std::string> LuaEngine::engineParameters;

// BASIC FUNCTIONS

void LuaEngine::create()
{
    if (exists()) return; // if already initialized, just return

	// before even opening lua, register internal variables
	EngineVariables::fill();

    L = lua_open();
    if (L)
    {
        hasState = true;
        initLibs();

        REFLECT_PYTHON( INTENSITY_VERSION_STRING );
        version = boost::python::extract<std::string>(INTENSITY_VERSION_STRING);

        engineParameters.clear();

        setupEmbedding();
        // after setting up embedding, we can fill lua too :)
        EngineVariables::fillLua();
    }
}

void LuaEngine::destroy()
{
    if (!exists()) return;

	EngineVariables::clear();
    lua_close(L);
    hasState = false;
}

bool LuaEngine::exists()
{
    return hasState;
}

// CHECKERS

bool LuaEngine::isNumber(int idx)
{
    if (!exists()) return false;
    return lua_isnumber(L, idx);
}

bool LuaEngine::isString(int idx)
{
    if (!exists()) return false;
    return lua_isstring(L, idx);
}

bool LuaEngine::isBool(int idx)
{
    if (!exists()) return false;
    return lua_isboolean(L, idx);
}

bool LuaEngine::isTable(int idx)
{
    if (!exists()) return false;
    return lua_istable(L, idx);
}

bool LuaEngine::isNoneNil(int idx)
{
    if (!exists()) return false;
    return lua_isnoneornil(L, idx);
}

// GETTERS

int LuaEngine::getInteger(int idx, int def)
{
    if (!exists()) return 0;
    return (int)luaL_optint(L, idx, def);
}

double LuaEngine::getDouble(int idx, double def)
{
    if (!exists()) return 0;
    return (double)luaL_optnumber(L, idx, def);
}

bool LuaEngine::getBool(int idx, bool def)
{
    if (!exists()) return false;
    if (lua_isnoneornil(L, idx)) return def;
    else
    {
        if (!lua_isboolean(L, idx)) typerror(idx, "bool");
        return (bool)lua_toboolean(L, idx);
    }
    return def;
}

std::string LuaEngine::getString(int idx, std::string def)
{
    if (!exists()) return std::string();
    return std::string(luaL_optstring(L, idx, def.c_str()));
}

LogicEntityPtr LuaEngine::getCLogicEntity(int idx)
{
    LogicEntityPtr ret;
    int id = 0;

    pushValueFromIndex(idx);
    id = getTableInteger("uniqueId");
    pop(1);

    ret = LogicSystem::getLogicEntity(id);
    Logging::log(Logging::INFO, "Lua: getting the CLE for UID %d\r\n", id);

    if (!ret.get())
    {
        std::string err = "Cannot find CLE for entity ";
        err += Utility::toString(id);
        err += "\r\n";
        error(err);
    }
    return ret;
}

// PUSHERS

void LuaEngine::pushValue(int val)
{
    if (!exists()) return;
    lua_pushinteger(L, val);
}

void LuaEngine::pushValue(double val)
{
    if (!exists()) return;
    lua_pushnumber(L, val);
}

void LuaEngine::pushValue(std::string val)
{
    if (!exists()) return;
    lua_pushstring(L, val.c_str());
}

void LuaEngine::pushValue(bool val)
{
    if (!exists()) return;
    lua_pushboolean(L, val);
}

void LuaEngine::pushValue()
{
    if (!exists()) return;
    lua_pushnil(L);
}

void LuaEngine::pushValueFromIndex(int idx)
{
    if (!exists()) return;
    lua_pushvalue(L, idx);
}

void LuaEngine::shift()
{
    if (!exists()) return;
    lua_insert(L, -2);
}

// CALLERS

void LuaEngine::getGlobal(std::string name)
{
    if (!exists()) return;
    lua_getglobal(L, name.c_str());
}

void LuaEngine::setGlobal()
{
    if (!exists()) return;
    lua_settable(L, LUA_GLOBALSINDEX);
}

void LuaEngine::call(int numargs, int numres)
{
    if (!exists()) return;
    if (lua_pcall(L, numargs, numres, 0))
        Logging::log(Logging::ERROR, getError().c_str());
}

// RUNNERS

std::string LuaEngine::runFile(std::string filename)
{
    if (!exists()) return std::string();
    if (luaL_dofile(L, filename.c_str()))
    {
        std::string msg = getError();
        Logging::log(Logging::ERROR, msg.c_str());
        return msg;
    }
    else return std::string();
}

std::string LuaEngine::runScript(std::string script)
{
    if (!exists()) return std::string();
    if (luaL_dostring(L, script.c_str()))
    {
        std::string msg = getError();
        Logging::log(Logging::ERROR, msg.c_str());
        return msg;
    }
    else return std::string();
}

// note: q66: generic command for console, before i rip off cubescript's head
ICOMMAND(run_script, "s", (char *s), LuaEngine::runScript(std::string(s)));

std::string LuaEngine::runScriptString(std::string script)
{
    if (!exists()) return std::string();
    if (luaL_dostring(L, script.c_str())) return std::string();
    std::string ret = getString(-1);
    pop(1);
    return ret;
}

int LuaEngine::runScriptInt(std::string script)
{
    if (!exists()) return 0;
    if (luaL_dostring(L, script.c_str())) return 0;
    int ret = getInteger(-1);
    pop(1);
    return ret;
}

double LuaEngine::runScriptDouble(std::string script)
{
    if (!exists()) return 0;
    if (luaL_dostring(L, script.c_str())) return 0;
    double ret = getDouble(-1);
    pop(1);
    return ret;
}

// OTHER FUNCTIONS

void LuaEngine::pop(int elem)
{
    if (!exists()) return;
    lua_pop(L, elem);
}

void LuaEngine::error(std::string msg)
{
    if (!exists()) return;
    luaL_where(L, 1);
    pushValue(msg);
    lua_concat(L, 2);
    Logging::log(Logging::ERROR, getString(-1).c_str());
    lua_error(L);
}

// TODO: better typerror (more info, and don't count self)
void LuaEngine::typerror(int narg, std::string tname)
{
    if (!exists()) return;
    defformatstring(buf)("bad argument %i (%s expected, got %s)", narg, tname.c_str(), lua_typename(L, lua_type(L, narg)));
    error(std::string(buf));
}

std::string LuaEngine::getError()
{
    std::string err = getString(-1);
    if (err.empty()) return "Unknown error from Lua";
    else return err;
}

int LuaEngine::gettop()
{
    if (!exists()) return 0;
    return lua_gettop(L);
}

// TABLES

void LuaEngine::newTable()
{
    if (!exists()) return;
    lua_newtable(L);
}

void LuaEngine::getTableItem(std::string name)
{
    if (!exists()) return;
    pushValue(name);
    lua_gettable(L, -2);
}

void LuaEngine::getTableItem(int idx)
{
    if (!exists()) return;
    pushValue(idx);
    lua_gettable(L, -2);
}

int LuaEngine::getTableInteger(std::string name, int def)
{
    if (!exists()) return 0;
    getTableItem(name);
    int ret = getInteger(-1, def);
    pop(1);
    return ret;
}

int LuaEngine::getTableInteger(int idx, int def)
{
    if (!exists()) return 0;
    getTableItem(idx);
    int ret = getInteger(-1, def);
    pop(1);
    return ret;
}

double LuaEngine::getTableDouble(std::string name, double def)
{
    if (!exists()) return 0;
    getTableItem(name);
    double ret = getDouble(-1, def);
    pop(1);
    return ret;
}

double LuaEngine::getTableDouble(int idx, double def)
{
    if (!exists()) return 0;
    getTableItem(idx);
    double ret = getDouble(-1, def);
    pop(1);
    return ret;
}

std::string LuaEngine::getTableString(std::string name, std::string def)
{
    if (!exists()) return std::string();
    getTableItem(name);
    std::string ret = getString(-1, def);
    pop(1);
    return ret;
}

std::string LuaEngine::getTableString(int idx, std::string def)
{
    if (!exists()) return std::string();
    getTableItem(idx);
    std::string ret = getString(-1, def);
    pop(1);
    return ret;
}

bool LuaEngine::getTableBool(std::string name, bool def)
{
    if (!exists()) return false;
    getTableItem(name);
    bool ret = getBool(-1, def);
    pop(1);
    return ret;
}

bool LuaEngine::getTableBool(int idx, bool def)
{
    if (!exists()) return false;
    getTableItem(idx);
    bool ret = getBool(-1, def);
    pop(1);
    return ret;
}

void LuaEngine::setTable(std::string name, int val)
{
    if (!exists()) return;
    pushValue(name);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(int idx, int val)
{
    if (!exists()) return;
    pushValue(idx);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(std::string name, double val)
{
    if (!exists()) return;
    pushValue(name);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(int idx, double val)
{
    if (!exists()) return;
    pushValue(idx);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(std::string name, std::string val)
{
    if (!exists()) return;
    pushValue(name);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(int idx, std::string val)
{
    if (!exists()) return;
    pushValue(idx);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(std::string name, bool val)
{
    if (!exists()) return;
    pushValue(name);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTable(int idx, bool val)
{
    if (!exists()) return;
    pushValue(idx);
    pushValue(val);
    lua_settable(L, -3);
}

void LuaEngine::setTableIndex()
{
	if (!exists()) return;
	lua_settable(L, -3);
}

int LuaEngine::next(int idx)
{
    if (!exists()) return 0;
    return lua_next(L, idx);
}

// REFERENCES

int LuaEngine::ref()
{
    if (!exists()) return 0;
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

void LuaEngine::getRef(int ref)
{
    if (!exists()) return;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
}

void LuaEngine::unref(int ref)
{
    if (!exists()) return;
    luaL_unref(L, LUA_REGISTRYINDEX, ref);
}

// FILE/SCRIPT LOAD

std::string LuaEngine::loadFile(std::string filename)
{
    if (!exists()) return std::string();
    if (luaL_loadfile(L, filename.c_str()))
    {
        std::string msg = getError();
        Logging::log(Logging::ERROR, msg.c_str());
        return msg;
    }
    else return std::string();
}

std::string LuaEngine::loadScript(std::string script)
{
    if (!exists()) return std::string();
    if (luaL_loadstring(L, script.c_str()))
    {
        std::string msg = getError();
        Logging::log(Logging::ERROR, msg.c_str());
        return msg;
    }
    else return std::string();
}
