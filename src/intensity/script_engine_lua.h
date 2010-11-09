 /* Copyright 2010 q66 <quaker66@gmail.com>
 * 
 * The file is part of CubeCreate project, which is licensed under MIT license.
 * The license file should be bundled with your CubeCreate distribution.
 * 
 */

/**
 * @mainpage Lua
 * 
 * @author q66 <quaker66@gmail.com>
 * @date 2010
 */

#include <lua.hpp>
#include <vector>
#include <set>

/**
 * @defgroup Lua_Engine_Group LuaEngine
 *
 * @{
 */

/**
 * @class LuaEngine
 * Basic class containing functions to control the Lua engine and the handle itself.
 */
class LuaEngine
{
  public:
    /** A map storing internal Lua engine paramters, not meant to be accessible from scripts. */
    static std::map<std::string, std::string> engineParameters; 

    /**
     * @brief Initialize the Lua engine.
     * 
     * Initializes the Lua stack, opens base libraries, sets up extensions,
     * clears the parameters, exports version into Lua and sets up script embedding.
     */
    static void create();
    /**
     * @brief Destroy the Lua engine.
     * 
     * Clears the engine and destroys the stack.
     */
    static void destroy();
    /**
     * @brief Check if Lua engine exists.
     * @return true if initialized, otherwise false.
     * 
     * Public accessor to hasState variable. If create() was called before, then it's initialized.
     */
    static bool exists();

    /**
     * @brief Check for type on stack.
     * @param idx The position of checked item on stack.
     * @return true if checked type is right, otherwise false.
     * 
     * Checks if type of item on stack specified by @p idx is number.
     */
    static bool isNumber(int idx);
    /**
     * @brief Check for type on stack.
     * @param idx The position of checked item on stack.
     * @return true if checked type is right, otherwise false.
     * 
     * Checks if type of item on stack specified by @p idx is string.
     */
    static bool isString(int idx);
    /**
     * @brief Check for type on stack.
     * @param idx The position of checked item on stack.
     * @return true if checked type is right, otherwise false.
     * 
     * Checks if type of item on stack specified by @p idx is boolean.
     */
    static bool isBool(int idx);
    /**
     * @brief Check for type on stack.
     * @param idx The position of checked item on stack.
     * @return true if checked type is right, otherwise false.
     * 
     * Checks if type of item on stack specified by @p idx is table.
     */
    static bool isTable(int idx);
    /**
     * @brief Check for type on stack.
     * @param idx The position of checked item on stack.
     * @return true if checked type is right, otherwise false.
     * 
     * Checks if type of item on stack specified by @p idx is none or nil.
     */
    static bool isNoneNil(int idx);

    /**
     * @brief Get item from stack.
     * @param idx The position of item on stack.
     * @param def The default value to set if the item is none or nil.
     * @return The integer present on stack in @p idx, and @p def if none/nil is present.
     * 
     * Gets item from stack in @p idx, returning it as int.
     * note: @p def is optional.
     */
    static int getInteger(int idx, int def = 0);
    /**
     * @brief Get item from stack.
     * @param idx The position of item on stack.
     * @param def The default value to set if the item is none or nil.
     * @return The double present on stack in @p idx, and @p def if none/nil is present.
     * 
     * Gets item from stack in @p idx, returning it as double.
     * note: @p def is optional.
     */
    static double getDouble(int idx, double def = 0);
    /**
     * @brief Get item from stack.
     * @param idx The position of item on stack.
     * @param def The default value to set if the item is none or nil.
     * @return The boolean present on stack in @p idx, and @p def if none/nil is present.
     * 
     * Gets item from stack in @p idx, returning it as boolean.
     * note: @p def is optional.
     */
    static bool getBool(int idx, bool def = false);
    /**
     * @brief Get item from stack.
     * @param idx The position of item on stack.
     * @param def The default value to set if the item is none or nil.
     * @return The string present on stack in @p idx, and @p def if none/nil is present.
     * 
     * Gets item from stack in @p idx, returning it as string.
     * note: @p def is optional.
     */
    static std::string getString(int idx, std::string def = std::string());
    /**
     * @brief Get item from stack.
     * @param idx The position of item on stack.
     * @return The CLogicEntity pointer based on its scripting equivalent on stack in @p idx.
     * 
     * Gets logic entity pointer based on its scripting equivalent on stack in @p idx and returns it.
     */
    static LogicEntityPtr getCLogicEntity(int idx);

    /**
     * @brief Push item to stack.
     * @param val The value to push on stack.
     * 
     * Push @p val of integer type on stack.
     */
    static void pushValue(int val);
    /**
     * @brief Push item to stack.
     * @param val The value to push on stack.
     * 
     * Push @p val of double type on stack.
     */
    static void pushValue(double val);
    /**
     * @brief Push item to stack.
     * @param val The value to push on stack.
     * 
     * Push @p val of string type on stack.
     */
    static void pushValue(std::string val);
    /**
     * @brief Push item to stack.
     * @param val The value to push on stack.
     * 
     * Push @p val of boolean type on stack.
     */
    static void pushValue(bool val);
    /**
     * @brief Push nil value to stack.
     * 
     * Push nil value to stack.
     */
    static void pushValue();
    /**
     * @brief Push item present somewhere on stack onto stack.
     * @param idx The position of item on stack.
     * 
     * Push value present on stack in @p idx onto stack.
     */
    static void pushValueFromIndex(int idx);
    /**
     * @brief Shift -2 and -1 on stack.
     * 
     * After calling this function, -2 becomes -1 and -1 becomes -2.
     */
    static void shift();

    /**
     * @brief Get a global variable from Lua and push it onto stack.
     * @param name The name of the global variable present in Lua.
     * 
     * Get a global variable specified by @p name from Lua and push it onto stack.
     */
    static void getGlobal(std::string name);
    /**
     * @brief Push an item from stack to lua globals.
     * 
     * Gets an item from stack (position -1) and pushes it into lua global variables.
     * The item gets automatically pop'd, so you don't have to do so manually.
     */
    static void setGlobal();
    /**
     * @brief Call a function.
     * @param numargs The number of arguments Lua should get from stack.
     * @param numres Number of items the function returns, controls how many values get pushed to stack.
     * 
     * Calls a function. If the call fails, it gets logged.
     * Results are push'd to stack and arguments are got from stack.
     * The function itself and its arguments get pop'd from stack automatically.
     * As for results, you have to pop them manually after you get them.
     * Example:
     * 
     * @code
     * LuaEngine::getGlobal("foo"); // first, the function is got
     * // let's assume it takes 3 arguments and returns 2 results
     * LuaEngine::pushValue(10); // first argument
     * LuaEngine::pushValue("bar");
     * LuaEngine::pushValue(false); // last argument
     * // now we have function on -4, first arg on -3, second on -2, last on -1.
     * // first argument specifies that -1, -2, -3 are filled with args, so -4 is function
     * // second argument specifies that results will be push'd on -1 (second result) and -2 (first result)
     * LuaEngine::call(3, 2);
     * // there are no function nor arguments on stack. There are two results instead.
     * int meh = LuaEngine::getInteger(-2); // first result
     * bool bleh = LuaEngine::getBool(-1); // second result
     * LuaEngine::pop(2); // let's pop two last items (the results) from stack
     * @endcode
     */
    static void call(int numargs, int numres);

    /**
     * @brief Run a Lua script from file.
     * @param filename The path (relative or absolute) to file you want to run.
     * @return empty string on success; error message if it fails.
     * 
     * Run a Lua script from file. Relative path assumes you're starting in CubeCreate directory.
     * Remember, if you "return" from the script, value gets push'd on stack, so you'll have to pop it!
     * Result pushing behaves in the same way as when calling.
     * @see call()
     * @see loadFile()
     */
    static std::string runFile(std::string filename);
    /**
     * @brief Run a Lua script from string.
     * @param script The string containing the script to run.
     * @return empty string on success; error message if it fails.
     * 
     * Run a Lua script from string. Returning works in the same way as when running a file.
     * You don't usually return from scripts ran using this function, because there are special calls for this.
     * Use this for strings with return only if you need to get results and still have error message returned from here.
     * @see runFile()
     * @see runScriptString()
     * @see runScriptInt()
     * @see runScriptDouble()
     */
    static std::string runScript(std::string script);
    /**
     * @brief Run a Lua script from string.
     * @param script The string containing the script to run.
     * @return return value of script (if string), if no string returned, then empty string
     * 
     * Run a Lua script from string. If the script returns a string, then this function returns the value.
     * If not, then it returns empty string. Unlike runScript, the value is automatically got and pop'd,
     * so you don't have to do so manually, but errors are not handled in this case.
     * If you want to handle errors, use standard runScript and get and pop the result from stack manually.
     * @see runScript()
     * @see runScriptInt()
     * @see runScriptDouble()
     * @see loadScript()
     */
    static std::string runScriptString(std::string script);
    /**
     * @brief Run a Lua script from string.
     * @param script The string containing the script to run.
     * @return return value of script (if integer), if no integer returned, then 0
     * 
     * Run a Lua script from string. If the script returns an integer, then this function returns the value.
     * If not, then it returns 0. Unlike runScript, the value is automatically got and pop'd,
     * so you don't have to do so manually, but errors are not handled in this case.
     * If you want to handle errors, use standard runScript and get and pop the result from stack manually.
     * @see runScript()
     * @see runScriptString()
     * @see runScriptDouble()
     */
    static int runScriptInt(std::string script);
    /**
     * @brief Run a Lua script from string.
     * @param script The string containing the script to run.
     * @return return value of script (if number), if no number returned, then empty string
     * 
     * Run a Lua script from string. If the script returns a lua number (either integer or double),
     * then this function returns the value as double.
     * If not, then it returns 0. Unlike runScript, the value is automatically got and pop'd,
     * so you don't have to do so manually, but errors are not handled in this case.
     * If you want to handle errors, use standard runScript and get and pop the result from stack manually.
     * @see runScript()
     * @see runScriptInt()
     * @see runScriptString()
     */
    static double runScriptDouble(std::string script);

    /**
     * @brief Pop element(s) from stack.
     * @param elem Number of elements to pop from stack.
     * 
     * Pops @p elem elements from stack. (Like, for @p elem = 3, items on -1, -2 and -3 are pop'd)
     */
    static void pop(int elem);
    /**
     * @brief Throw an error.
     * @param msg Message to be added to error.
     * 
     * Logs @p msg with additional information (line number etc) into CubeCreate's log system and does the same with lua itself.
     */
    static void error(std::string msg);
    /**
     * @brief Throw a type error.
     * @param narg The wrong argument number.
     * @param tname Name of expected type on @p idx.
     * 
     * Generates error message in format "location: bad argument @p narg (@p tname expected, got 'actualtype').
     * The message gets logged first into CubeCreate's log system and then thrown to Lua too.
     */
    static void typerror(int narg, std::string tname);
    /**
     * @brief Get last error message.
     * @return Error message.
     * 
     * Gets the error message from last failed and returns it as string.
     */
    static std::string getError();
    /**
     * @brief Get index of top item on stack.
     * @return Index of top item on stack.
     * 
     * Gets the index of top item on stack, useful for looping all types on stack.
     */
    static int gettop();

    /**
     * @brief Creates a new table and pushes it on stack.
     * 
     * Creates a new Lua table and pushes it on stack.
     */
    static void newTable();
    /**
     * @brief Gets an item from table (hash) onto stack.
     * @param name Name of the item in table.
     * 
     * Gets an item of name @p name from table on -1 onto stack.
     * Then it's up to you to get it as any type on -1 on stack,
     * and pop it after you don't need it anymore, because it doesn't get auto-pop'd.
     */
    static void getTableItem(std::string name);
    /**
     * @brief Gets an item from table (array) onto stack.
     * @param idx Index of item in table, begins with 1.
     * 
     * Gets an item of index @p name from table on -1 onto stack.
     * Then it's up to you to get it as any type on -1 on stack,
     * and pop it after you don't need it anymore, because it doesn't get auto-pop'd.
     */
    static void getTableItem(int idx);
    /**
     * @brief Gets an item from table (hash).
     * @param name Name of the item in table.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as integer.
     * 
     * Gets an item of name @p name from table and returns it as integer.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static int getTableInteger(std::string name, int def = 0);
    /**
     * @brief Gets an item from table (hash).
     * @param idx Index of item in table, begins with 1.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as integer.
     * 
     * Gets an item of name @p name from table and returns it as integer.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static int getTableInteger(int idx, int def = 0);
    /**
     * @brief Gets an item from table (hash).
     * @param name Name of the item in table.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as double.
     * 
     * Gets an item of name @p name from table and returns it as double.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static double getTableDouble(std::string name, double def = 0);
    /**
     * @brief Gets an item from table (hash).
     * @param idx Index of item in table, begins with 1.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as double.
     * 
     * Gets an item of name @p name from table and returns it as double.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static double getTableDouble(int idx, double def = 0);
    /**
     * @brief Gets an item from table (hash).
     * @param name Name of the item in table.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as string.
     * 
     * Gets an item of name @p name from table and returns it as string.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static std::string getTableString(std::string name, std::string def = std::string());
    /**
     * @brief Gets an item from table (hash).
     * @param idx Index of item in table, begins with 1.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as string.
     * 
     * Gets an item of name @p name from table and returns it as string.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static std::string getTableString(int idx, std::string def = std::string());
    /**
     * @brief Gets an item from table (hash).
     * @param name Name of the item in table.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as boolean.
     * 
     * Gets an item of name @p name from table and returns it as boolean.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static bool getTableBool(std::string name, bool def = false);
    /**
     * @brief Gets an item from table (hash).
     * @param idx Index of item in table, begins with 1.
     * @param def Default value to return if element value is none/nil.
     * @return The value of item in table as boolean.
     * 
     * Gets an item of name @p name from table and returns it as boolean.
     * It gets auto-pop'd, so you don't have to care about it anymore.
     */
    static bool getTableBool(int idx, bool def = false);
    /**
     * @brief Sets a table item value.
     * @param name Name of the item in table.
     * @param val Integer value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(std::string name, int val);
    /**
     * @brief Sets a table item value.
     * @param idx Index of item in table, begins with 1.
     * @param val Integer value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(int idx, int val);
    /**
     * @brief Sets a table item value.
     * @param name Name of the item in table.
     * @param val Double value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(std::string name, double val);
    /**
     * @brief Sets a table item value.
     * @param idx Index of item in table, begins with 1.
     * @param val Double value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(int idx, double val);
    /**
     * @brief Sets a table item value.
     * @param name Name of the item in table.
     * @param val String value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(std::string name, std::string val);
    /**
     * @brief Sets a table item value.
     * @param idx Index of item in table, begins with 1.
     * @param val String value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(int idx, std::string val);
    /**
     * @brief Sets a table item value.
     * @param name Name of the item in table.
     * @param val Boolean value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(std::string name, bool val);
    /**
     * @brief Sets a table item value.
     * @param idx Index of item in table, begins with 1.
     * @param val Boolean value to set.
     * 
     * Sets value of key @p name in table on -1 to @p val.
     * Creates the item if needed.
     */
    static void setTable(int idx, bool val);
    /**
     * @brief Sets a table item from stack.
     * 
     * Gets table from -3, key from -2 and value from -1.
     * Automatically creates the item in table if none of the key
     * exists. If it exists already, it'll get overwritten.
     */
    static void setTableIndex();
    /**
     * @brief Pops a key (or array index) from stack, pushes a key/index-value pair on given index.
     * @param idx Index of table on stack.
     * @return 0 when there are no more items on stack, 1 otherwise.
     * 
     * Pops a key/index from stack, pushes a key/index-value pair from table at given index.
     * Useful for iterating over the table.
     * 
     * @code
     * LuaEngine::getGlobal("foobar"); // get table foobar from globals on stack
     * LuaEngine::pushValue(); // something to begin with, nil is enough
     * // we assume our table is a hash (has string keys) and values are all numbers.
     * // the procedure for i.e. array is simillar, you just get key as integer, not as string.
     * while (LuaEngine::next(-2)) // repeat until it returns 0
     * {
     *     std::string key = LuaEngine::getString(-2);
     *     double value = LuaEngine::getNumber(-1);
     *     // do more code
     *     ...
     *     // and now pop the value; keep key for next iteration though -
     *     // that's why we pushed nil at beginning, for first iteration so it has something to eat
     *     LuaEngine::pop(1);
     * }
     * @endcode
     */
    static int next(int idx);

    /**
     * @brief Get an unique reference number for stack item at -1.
     * @return Item's unique reference number.
     * 
     * Gets an item on -1 and creates and returns a reference -
     * that's an unique number which can be later re-used.
     * The item gets pop'd from stack after ref'ing it.
     * 
     * Reference can be later used to get the item again at any place.
     * @see getRef()
     * @see unref()
     */
    static int ref();
    /**
     * @brief Push an item on stack based on reference number.
     * @param ref Reference number of item to get.
     * 
     * Gets an item previously referenced with ref() on stack again.
     * Then, you can access it on -1.
     * You'll have to pop the item manually after it's not needed anymore.
     * @see ref()
     * @see unref()
     */
    static void getRef(int ref);
    /**
     * @brief Releases the reference number and the item.
     * @param ref Reference to release.
     * 
     * Releases the reference number so it can't be re-used and so does with the item.
     * @see ref()
     * @see getRef()
     */
    static void unref(int ref);

    /**
     * @brief Load a file, but don't run it.
     * @param filename The path (relative or absolute) to file you want to load.
     * @return empty string on success; error message if it fails.
     * 
     * Loads a file without running it. Useful for checking if the file is proper lua script.
     * @see runFile()
     */
    static std::string loadFile(std::string filename);
    /**
     * @brief Load a Lua script from string.
     * @param script The string containing the script to load.
     * @return empty string on success; error message if it fails.
     * 
     * Loads a script from string without running it. Useful for checking if the string is proper lua script.
     * @see runScript()
     */
    static std::string loadScript(std::string script);
  private:
    // Directory containing base lua library, src/lua by default.
    static std::string scriptDir;
    // Version of CubeCreate to be exposed to Lua (Global table)
    static std::string version;
    // Is the engine initialized?
    static bool hasState;
    // The lua state itself, created on create(), destroyed on destroy()
    // Checking done using hasState.
    static lua_State *L;
    // do we run tests? if true, then yes.
    static bool runTests;
    // were tests ran already? if yes, don't run them again
    static bool ranTests;
    /* Initialize base lua lubraries
     * 
     * Initializes base Lua libraries, like math, table, string and stuff.
     */
    static void initLibs();
    /* Setup a library module
     * 
     * Executes a file being a "module" for lua base library from scriptDir.
     * Optionally, you can specify if to run tests for the module.
     */
    static void setupModule(std::string file, bool noTests = false);
    /* Setup script embedding
     * 
     * Exposes functions into Lua and initializes base library modules.
     */
    static void setupEmbedding();
};

/**
 * @def LUA_EMBED_GEN
 * @brief Macro serving as base for all autogenerated embedding macros.
 * @param name Name of global function to define for embed
 * @param numreturns Number of items the function returns onto stack
 * @param arguments_def Default argument definitions
 * @param wrapped_code The code to wrap itself
 * 
 * This macro serves as helper so it isn't needed to repeat code too much
 * and also makes the functions "hide" a bit, like, not showing the user the lua_State.
 * Also logs some stuff and returns the number of arguments as required.
 * Remember, you shouldn't use this macro directly.
 */
#define LUA_EMBED_GEN(name, numreturns, arguments_def, wrapped_code) \
int name(lua_State *L) \
{ \
    Logging::log(Logging::INFO, "Registering Lua function: %s\r\n", #name); \
    arguments_def; \
\
    wrapped_code; \
\
    return numreturns; \
}

/**
 * @def LUA_EMBED_NOPARAM
 * @brief Simplest version of wrapped macro around LUA_EMBED_GEN, function without args.
 * @param name Name of embedded lua function. Automatically prepends __script__ to real C function name
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * This macro wraps over LUA_EMBED_GEN. Provides simplest version,  a function accepting no arguments.
 * @see LUA_EMBED_GEN
 */
#define LUA_EMBED_NOPARAM(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, {}, wrapped_code)

// include autogenerated macros. Those are, btw, all documented too.
#include "script_engine_lua_generated.h"

// Object macros

/**
 * @def LUA_EMBED_T
 * @brief Wrapper over LUA_EMBED_o* autogenerated functions used to manipulate with logic entities.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param type_codes Argument types to append to first argument "object" - LUA_EMBED_oXXX.
 * @param wrapped_code The code to wrap itself
 * 
 * This macro wraps over LUA_EMBED_oXXX. First argument (the scripting entity) gets converted to
 * CLogicEntity pointer, which is named "self" inside the function.
 * Other arguments behave in a standard way, and their definitions are based on @p type_codes.
 * See the difference with LUA_EMBED_Z - this one gets C version of logic entity,
 * LUA_EMBED_Z gets scripting entity and references it.
 * @see LUA_EMBED_Z()
 */
#define LUA_EMBED_T(name, numreturns, type_codes, wrapped_code) \
    LUA_EMBED_o##type_codes(name, numreturns, { \
        Logging::log(Logging::INFO, "Registering Lua LogicEntityPtr function: %s\r\n", #name); \
        LogicEntityPtr self = LuaEngine::getCLogicEntity(1); \
        wrapped_code; \
    });

/**
 * @def LUA_EMBED_Z
 * @brief Wrapper over LUA_EMBED_o* autogenerated functions used to manipulate with scripting entities.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param type_codes Argument types to append to first argument "object" - LUA_EMBED_oXXX.
 * @param wrapped_code The code to wrap itself
 * 
 * This macro wraps over LUA_EMBED_oXXX. Lua reference unique number is got for first argument (object)
 * and named "ref" for later usage. (for example to pass it to some function)
 * Other arguments behave in a standard way, and their definitions are based on @p type_codes.
 * See the difference with LUA_EMBED_T - this one gets scripting entity and references it,
 * LUA_EMBED_T gets the C version of logic entity directly.
 * @see LUA_EMBED_T()
 */
#define LUA_EMBED_Z(name, numreturns, type_codes, wrapped_code) \
    LUA_EMBED_o##type_codes(name, numreturns, { \
        Logging::log(Logging::INFO, "Getting reference unique ID for Lua function: %s\r\n", #name); \
        if (!LuaEngine::isTable(1)) \
        { \
            LuaEngine::typerror(1, "table"); \
            return 0; \
        } \
        LuaEngine::pushValueFromIndex(1); \
        int ref = LuaEngine::ref(); \
        wrapped_code; \
    });

/**
 * @def LUA_TABLE_LOOP
 * @brief Loop a table. Basically just wraps around standard while and LuaEngine::next.
 * @param wrapped_code The code to run on every repeat
 * 
 * Macro to wrap over LuaEngine::next and while loop to simplify table looping.
 * For example, minimizes manual popping, pushing of nil etc.
 * Example:
 * @code
 * LuaEngine::runScript("foo = { a = 1, b = 2, c = 3 } bar = { 5, 10, 15, 20, 25 }");
 * LuaEngine::getGlobal("foo"); // loop hash
 * LUA_TABLE_LOOP({
 *     // in hash, we have key on -2, which is a string,
 *     // and value of any type on -1, in our case integer.
 *     printf("key: %s, value: %i\n", LuaEngine::getString(-2), LuaEngine::getInteger(-1));
 *     // as you can see, no popping needed, done automatically.
 * });
 * LuaEngine::pop(1); // pop the table from stack when it's not needed anymore.
 * LuaEngine::getGlobal("bar"); // loop array
 * LUA_TABLE_LOOP({
 *     // in array, we have index on -2, which is an integer,
 *     // and value of any type on -1, in our case integer.
 *     printf("index: %i, value: %i\n", LuaEngine::getInteger(-2), LuaEngine::getInteger(-1));
 *     // as you can see, no popping needed, done automatically.
 * });
 * LuaEngine::pop(1);
 * @endcode
 */
#define LUA_TABLE_LOOP(wrapped_code) \
{ \
    LuaEngine::pushValue(); \
    while (LuaEngine::next(-2)) \
    { \
        wrapped_code; \
        LuaEngine::pop(1); \
    } \
}

/**
 * @}
 */
