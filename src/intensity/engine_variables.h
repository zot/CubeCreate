 /* Copyright 2010 q66 <quaker66@gmail.com>
 * 
 * The file is part of CubeCreate project, which is licensed under MIT license.
 * The license file should be bundled with your CubeCreate distribution.
 * 
 */

/**
 * @mainpage Engine Variables
 * 
 * @author q66 <quaker66@gmail.com>
 * @date 2010
 */

/**
 * @defgroup Lua_Engine_Group LuaEngine
 *
 * @{
 */

#ifdef __clang__
# define __clang_block __block
# undef __block
#endif

# include <iostream>
# include <map>
# include <set>

// there is shared_ptr in graph's branch, remove
#include <boost/shared_ptr.hpp>
// there is anytype in graph's branch too
#include <boost/any.hpp>

#define anyint boost::any_cast<int>
#define anyfloat boost::any_cast<float>
#define anystring boost::any_cast<std::string>

#ifdef __clang__
# define __block __clang_block
# undef __clang_block
#endif

#ifdef __clang__
# define _cb_ ^
# define _lambda_ ^
#else
# define _cb_ *
# define _lambda_ []
#endif

/**
 * @class EngineVariable
 * Basic class representing engine variable.
 */
class EngineVariable
{
public:
    /**
     * @brief Integer variable constructor.
     * @param vname Name of future variable.
     * @param minvi Minimal value of variable.
     * @param curvi Default value of variable.
     * @param maxvi Maximal value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * @param override Sets if the variable is overridable (i.e. gets re-set through lua reinitializations). Defaults to false.
     * 
     * Construct an integer variable.
     */
	EngineVariable(
		const std::string& vname,
		int minvi,
		int curvi,
		int maxvi,
		void (_cb_ cb)(int, int, int, int) = NULL,
		bool persist = false,
		bool override = false
	);
    /**
     * @brief Float variable constructor.
     * @param vname Name of future variable.
     * @param minvf Minimal value of variable.
     * @param curvf Default value of variable.
     * @param maxvf Maximal value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * @param override Sets if the variable is overridable (i.e. gets re-set through lua reinitializations). Defaults to false.
     * 
     * Construct a float variable.
     */
	EngineVariable(
		const std::string& vname,
		float minvf,
		float curvf,
		float maxvf,
		void (_cb_ cb)(float, float, float, float) = NULL,
		bool persist = false,
		bool override = false
	);
    /**
     * @brief String variable constructor.
     * @param vname Name of future variable.
     * @param curvs Default value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * @param override Sets if the variable is overridable (i.e. gets re-set through lua reinitializations). Defaults to false.
     * 
     * Construct a string variable. Doesn't have min, max because it makes no sense for strings.
     */
	EngineVariable(
		const std::string& vname,
		const std::string& curvs,
		void (_cb_ cb)(const std::string&, const std::string&) = NULL,
		bool persist = false,
		bool override = false
	);
    /**
     * @brief Integer alias constructor.
     * @param aname Name of the alias.
     * @param val Value of the alias.
     * 
     * Construct an integer alias.
     */
	EngineVariable(
		const std::string& aname,
		int val,
		_UNUSED_ bool alias // hacky, fixme. It's used to make sure we're constructing actual alias
	);
    /**
     * @brief Float alias constructor.
     * @param aname Name of the alias.
     * @param val Value of the alias.
     * 
     * Construct a float alias.
     */
	EngineVariable(
		const std::string& aname,
		float val,
		_UNUSED_ bool alias
	);
    /**
     * @brief String alias constructor.
     * @param aname Name of the alias.
     * @param val Value of the alias.
     * 
     * Construct a string alias.
     */
	EngineVariable(
		const std::string& aname,
		const std::string& val,
		_UNUSED_ bool alias
	);
    /**
     * @brief Get a name of the variable.
     * @return A string containing name of the variable.
     * 
     * Get a name of the variable.
     */
	std::string getName();
    /**
     * @brief Get a type of the variable.
     * @return A string containing type of the variable.
     * 
     * Get a type of the variable.
     */
	std::string getType();
    /**
     * @brief Get a string value of the variable.
     * @return A string containing value of the variable.
     * 
     * Get a string value of the variable.
     */
	std::string getString();
    /**
     * @brief Get an integer value of the variable.
     * @return An integer containing value of the variable.
     * 
     * Get an integer value of the variable.
     */
	int getInteger();
    /**
     * @brief Get a float value of the variable.
     * @return A float containing value of the variable.
     * 
     * Get a float value of the variable.
     */
	float getFloat();
    /**
     * @brief Set an integer value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * @param forceCB Forces running a callback after value set. Defaults to false.
     * @param clamp If value is bigger than max or smaller than min, then it gets clamped. Defaults to true.
     * 
     * Sets an integer value of the variable.
     */
	void set(int val, bool luaSync = true, bool forceCB = false, bool clamp = true);
    /**
     * @brief Set a float value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * @param forceCB Forces running a callback after value set. Defaults to false.
     * @param clamp If value is bigger than max or smaller than min, then it gets clamped. Defaults to true.
     * 
     * Sets a float value of the variable.
     */
	void set(float val, bool luaSync = true, bool forceCB = false, bool clamp = true);
    /**
     * @brief Set a string value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * @param forceCB Forces running a callback after value set. Defaults to false.
     * 
     * Sets a string value of the variable.
     */
	void set(std::string val, bool luaSync = true, bool forceCB = false, _UNUSED_ bool dummy = true); // EEEEEK HACK DETECTED, find a better way! lazy coder
    /**
     * @brief Gets if the variable is persistent.
     * @return If persistent, then true, otherwise false.
     * 
     * Gets if the variable is persistent.
     */
	bool isPersistent();
    /**
     * @brief Gets if the variable is read only.
     * @return If read only, then true, otherwise false.
     * 
     * Gets if the variable is read only (only from Lua though!).
     */
	bool isReadOnly();
    /**
     * @brief Gets if the variable is overridable.
     * @return If overridable, then true, otherwise false.
     * 
     * Gets if the variable is overridable. That means, if it gets re-set through Lua engine reinitializations.
     */
	bool isOverridable();
    /**
     * @brief Gets if the variable is alias.
     * @return If alias, then true, otherwise false.
     * 
     * Gets if the variable is alias. That means that the range of values is not limited, it's written to cfg
     * and has no global since it's not initialized in a standard way. Also can't have callback. Doesn't handle persistency
     * in a standard way, too, can't be read only and is always non-overridable (gets stored through maps and restarts).
     */
	bool isAlias();
    /**
     * @brief Registers integer Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaIVAR();
    /**
     * @brief Registers float Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaFVAR();
    /**
     * @brief Registers string Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaSVAR();
private:
	// this one can call a callback if set; it also does a value sync with Lua which can call lua callback.
	void callCB(bool luaSync, bool forceCB);

	// is the var persistent?
	bool persistent;
	// has the var a C++ callback?
	bool hasCB;
	// var name
	std::string name;
	// var type
	std::string type;
	// is readonly (only from lua, C++ is writable)?
	bool readOnly;
	// is overridable
	bool override;
	// is alias
	bool alias;

	// anytypes storing the values
	boost::any prev;
	boost::any minv;
	boost::any curv;
	boost::any maxv;

	// union storing the callback (for memory save)
	union
	{
		void (_cb_ intCB)(int, int, int, int);
		void (_cb_ floatCB)(float, float, float, float);
		void (_cb_ stringCB)(const std::string&, const std::string&);
	};
};

/// Typedef map of string and variable ptr to EVMap for simpler syntax.
typedef std::map<std::string, EngineVariable *> EVMap;
/// Typedef pair of string and variable ptr to EVPair for simpler syntax.
typedef std::pair<std::string, EngineVariable *> EVPair;

/**
 * @class EngineVariables
 * Class representing storage for EngineVariable(Ptr)'s
 */
class EngineVariables
{
public:
    /**
     * @brief Register a variable into storage.
     * @param name Name of the variable.
     * @param var EngineVariable pointer representing the variable.
     * 
     * Register a variable into storage.
     */
	static void reg(const std::string& name, EngineVariable *var);
    /**
     * @brief Clear the storage (but save persistents in special map)
     * 
     * Clear the storage (but save persistents in special map)
     */
	static void clear();
    /**
     * @brief Flush the storage (free the memory from all storages)
     * 
     * Flush the storage (free the memory from all storages)
     */
	static void flush();
    /**
     * @brief Fill the storage from persistents and register all other vars.
     * 
     * Fill the storage from persistents and register all other vars. Doesn't fill Lua.
     */
	static void fill();
    /**
     * @brief Fill Lua script engine with variables from storage.
     * 
     * Fill Lua script engine with variables from storage.
     */
	static void fillLua();
    /**
     * @brief Fill storage from persistents.
     * 
     * Fill storage from persistents.
     */
	static void fillFromPersistent();
    /**
     * @brief Sync an integer value from Lua.
     * @param name Name of the variable.
     * @param value Integer value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, int value);
    /**
     * @brief Sync a float value from Lua.
     * @param name Name of the variable.
     * @param value Float value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, float value);
    /**
     * @brief Sync a string value from Lua.
     * @param name Name of the variable.
     * @param value String value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, const std::string& value);
    /**
     * @brief Get the EngineVariable pointer for specified name.
     * @param name Name of the variable to get shared ptr for.
     * @return The EngineVariable pointer for specified name.
     * 
     * Changes done with the returned ptr reflect in storage too, i.e.
     * @code
     * EngineVariables::get("blah")->set(5);
     * int woot = EngineVariables::get("blah")->getInteger();
     * @endcode
     */
	static EngineVariable *get(const std::string& name);
private:
	// storage and persistent storage. First one is cleared, second one is cleared just on persistent values transfer to standard storage.
	static EVMap storage;
	static EVMap persistentStorage; // used just on clear() - persistent vars get moved here
};

// extern all registered variables
#ifdef REGVAR
#undef REGVAR
#endif
#define REGVAR(name, ...) extern EngineVariable *_EV_##name
#define _EV_NODEF
#include "engine_variables_registers.h"
#undef _EV_NODEF
#undef REGVAR

/**
 * @def REGVAR
 * @brief Macro for simplifying variable registration.
 * @param name Name of the variable to register.
 * @param ... This differs for every variable.
 * 
 * For integer variable, you pass three integer values in addition to name (min, cur, max) and optionally a callback
 * (void closure or void) and boolean setting persistency - true means persistent. For float variable, it's the same
 * except passed values are floats. Callback for integer and float variables takes 4 integer/float arguments
 * (min, max, prev, cur). For string variable, you pass just cur value (no min, max),
 * and callback accepts just two arguments (prev and cur).
 */
#define REGVAR(name, ...) EngineVariable *_EV_##name = new EngineVariable(#name, __VA_ARGS__)

/**
 * @def ICB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for integer variables, letting @p code get minv, maxv, prev and curv values.
 * @code
 * REGVAR("foo", 0, 1, 2, ICB({ foo }));
 * @endcode
 */
#define ICB(code) _lambda_(_UNUSED_ int minv, _UNUSED_ int maxv, _UNUSED_ int prev, _UNUSED_ int curv) code

/**
 * @def FCB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for float variables, letting @p code get minv, maxv, prev and curv values.
 * @code
 * REGVAR("foo", 0.1, 1.3, 5.1, FCB({ foo }));
 * @endcode
 */
#define FCB(code) _lambda_(_UNUSED_ float minv, _UNUSED_ float maxv, _UNUSED_ float prev, _UNUSED_ float curv) code

/**
 * @def SCB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for string variables, letting @p code get prev and curv values.
 * @code
 * REGVAR("foo", "bar", SCB({ foo }));
 * @endcode
 */
#define SCB(code) _lambda_(_UNUSED_ const std::string& prev, _UNUSED_ const std::string& curv) code

/**
 * @def GETIV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as integer.
 * @code
 * int i = GETIV(foo);
 * @endcode
 */
#define GETIV(name) _EV_##name->getInteger()

/**
 * @def GETFV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as float.
 * @code
 * float d = GETFV(foo);
 * @endcode
 */
#define GETFV(name) _EV_##name->getFloat()

/**
 * @def GETSV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as string.
 * @code
 * std::string s = GETSV(foo);
 * @endcode
 */
#define GETSV(name) _EV_##name->getString()

/**
 * @def SETV
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name.
 * @code
 * SETV(foo, 15);
 * @endcode
 */
#define SETV(name, value) _EV_##name->set(value)

/**
 * @def SETVN
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name, not clamping its value
 * (allowing values smaller than min or bigger than max).
 * @code
 * SETVN(foo, 65536);
 * @endcode
 */
#define SETVN(name, value) _EV_##name->set(value, true, false, false)

/**
 * @def SETVF
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name, forcing its callback to run (if exists).
 * @code
 * SETVF(foo, 15);
 * @endcode
 */
#define SETVF(name, value) _EV_##name->set(value, true, true, true)

/**
 * @def SETVFN
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name, forcing its callback to run (if exists)
 * and not clamping its value (allowing values smaller than min or bigger than max).
 * @code
 * SETVFN(foo, 65536);
 * @endcode
 */
#define SETVFN(name, value) _EV_##name->set(value, true, true, false)

/**
 * @}
 */
