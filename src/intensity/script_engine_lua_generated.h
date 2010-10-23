
/**
 * @def LUA_EMBED_i
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments i.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_i(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        , wrapped_code)


/**
 * @def LUA_EMBED_s
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments s.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_s(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        , wrapped_code)


/**
 * @def LUA_EMBED_d
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments d.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_d(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        , wrapped_code)


/**
 * @def LUA_EMBED_o
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments o.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_o(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        , wrapped_code)


/**
 * @def LUA_EMBED_b
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments b.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_b(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        bool arg1 = LuaEngine::getBool(1); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_is
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments is.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_is(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        std::string arg2 = LuaEngine::getString(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ss
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ss.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ss(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_si
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments si.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_si(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        int arg2 = LuaEngine::getInteger(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_oi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments oi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_oi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        int arg2 = LuaEngine::getInteger(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ob
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ob.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ob(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        bool arg2 = LuaEngine::getBool(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_os
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments os.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_os(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        std::string arg2 = LuaEngine::getString(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_od
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments od.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_od(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        double arg2 = LuaEngine::getDouble(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ds
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ds.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ds(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        std::string arg2 = LuaEngine::getString(2); \
        , wrapped_code)


/**
 * @def LUA_EMBED_do
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments do.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_do(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        /* arg2 reserved for object */ \
        , wrapped_code)


/**
 * @def LUA_EMBED_iis
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iis.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iis(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        std::string arg3 = LuaEngine::getString(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sdd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sdd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sdd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sss
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sss.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sss(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        std::string arg3 = LuaEngine::getString(3); \
        , wrapped_code)


/**
 * @def LUA_EMBED_oddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments oddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_oddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiss
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiss.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiss(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        std::string arg3 = LuaEngine::getString(3); \
        std::string arg4 = LuaEngine::getString(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiis
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiis.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiis(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        std::string arg4 = LuaEngine::getString(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ssdi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ssdi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ssdi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        double arg3 = LuaEngine::getDouble(3); \
        int arg4 = LuaEngine::getInteger(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ssdd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ssdd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ssdd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sdddi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sdddi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sdddi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sssdd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sssdd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sssdd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        std::string arg3 = LuaEngine::getString(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sdddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sdddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sdddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_siidi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments siidi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_siidi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiss
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiss.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiss(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        std::string arg4 = LuaEngine::getString(4); \
        std::string arg5 = LuaEngine::getString(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiisi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiisi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiisi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        std::string arg4 = LuaEngine::getString(4); \
        int arg5 = LuaEngine::getInteger(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_idddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments idddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_idddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sdddii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sdddii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sdddii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dddddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dddddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dddddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iidddi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iidddi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iidddi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        int arg6 = LuaEngine::getInteger(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iisddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iisddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iisddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        std::string arg3 = LuaEngine::getString(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_idddsi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments idddsi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_idddsi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        std::string arg5 = LuaEngine::getString(5); \
        int arg6 = LuaEngine::getInteger(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ssiiid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ssiiid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ssiiid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        double arg6 = LuaEngine::getDouble(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        double arg6 = LuaEngine::getDouble(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sdddddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sdddddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sdddddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiiddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiiddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiiddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiddddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiddddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiddddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ssiiidi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ssiiidi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ssiiidi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiiiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiiiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiiiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_sddddid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments sddddid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_sddddid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        int arg6 = LuaEngine::getInteger(6); \
        double arg7 = LuaEngine::getDouble(7); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddiiid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddiiid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddiiid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iidddddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iidddddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iidddddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ssiiiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ssiiiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ssiiiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        std::string arg1 = LuaEngine::getString(1); \
        std::string arg2 = LuaEngine::getString(2); \
        int arg3 = LuaEngine::getInteger(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        , wrapped_code)


/**
 * @def LUA_EMBED_oidddiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments oidddiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_oidddiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        , wrapped_code)


/**
 * @def LUA_EMBED_idddidddi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments idddidddi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_idddidddi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        int arg5 = LuaEngine::getInteger(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dddsiiidi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dddsiiidi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dddsiiidi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        std::string arg4 = LuaEngine::getString(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiidddidii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiidddidii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiidddidii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddiiid
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddiiid.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddiiid(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        double arg10 = LuaEngine::getDouble(10); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dddiiiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dddiiiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dddiiiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        int arg4 = LuaEngine::getInteger(4); \
        int arg5 = LuaEngine::getInteger(5); \
        int arg6 = LuaEngine::getInteger(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddiiidi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddiiidi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddiiidi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        double arg10 = LuaEngine::getDouble(10); \
        int arg11 = LuaEngine::getInteger(11); \
        , wrapped_code)


/**
 * @def LUA_EMBED_osiddddddii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments osiddddddii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_osiddddddii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        std::string arg2 = LuaEngine::getString(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        double arg9 = LuaEngine::getDouble(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiidddidiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiidddidiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiidddidiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iissdddiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iissdddiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iissdddiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        std::string arg3 = LuaEngine::getString(3); \
        std::string arg4 = LuaEngine::getString(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiddddddidi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiddddddidi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiddddddidi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        double arg10 = LuaEngine::getDouble(10); \
        int arg11 = LuaEngine::getInteger(11); \
        , wrapped_code)


/**
 * @def LUA_EMBED_ddddddiiidii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments ddddddiiidii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_ddddddiiidii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        double arg10 = LuaEngine::getDouble(10); \
        int arg11 = LuaEngine::getInteger(11); \
        int arg12 = LuaEngine::getInteger(12); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiidddidiiibi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiidddidiiibi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiidddidiiibi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        bool arg12 = LuaEngine::getBool(12); \
        int arg13 = LuaEngine::getInteger(13); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiidddidiibibi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiidddidiibibi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiidddidiibibi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        bool arg11 = LuaEngine::getBool(11); \
        int arg12 = LuaEngine::getInteger(12); \
        bool arg13 = LuaEngine::getBool(13); \
        int arg14 = LuaEngine::getInteger(14); \
        , wrapped_code)


/**
 * @def LUA_EMBED_iiddddddidib
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments iiddddddidib.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_iiddddddidib(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        int arg2 = LuaEngine::getInteger(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        double arg10 = LuaEngine::getDouble(10); \
        int arg11 = LuaEngine::getInteger(11); \
        bool arg12 = LuaEngine::getBool(12); \
        , wrapped_code)


/**
 * @def LUA_EMBED_idddddddiiii
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments idddddddiiii.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_idddddddiiii(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        int arg12 = LuaEngine::getInteger(12); \
        , wrapped_code)


/**
 * @def LUA_EMBED_idddddiidddi
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments idddddiidddi.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_idddddiidddi(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        int arg1 = LuaEngine::getInteger(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        int arg7 = LuaEngine::getInteger(7); \
        int arg8 = LuaEngine::getInteger(8); \
        double arg9 = LuaEngine::getDouble(9); \
        double arg10 = LuaEngine::getDouble(10); \
        double arg11 = LuaEngine::getDouble(11); \
        int arg12 = LuaEngine::getInteger(12); \
        , wrapped_code)


/**
 * @def LUA_EMBED_dddddddiiidddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments dddddddiiidddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_dddddddiiidddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        double arg1 = LuaEngine::getDouble(1); \
        double arg2 = LuaEngine::getDouble(2); \
        double arg3 = LuaEngine::getDouble(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        int arg8 = LuaEngine::getInteger(8); \
        int arg9 = LuaEngine::getInteger(9); \
        int arg10 = LuaEngine::getInteger(10); \
        double arg11 = LuaEngine::getDouble(11); \
        double arg12 = LuaEngine::getDouble(12); \
        double arg13 = LuaEngine::getDouble(13); \
        double arg14 = LuaEngine::getDouble(14); \
        , wrapped_code)


/**
 * @def LUA_EMBED_osiddddddiidddd
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments osiddddddiidddd.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\n
 * -----------------------------\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si("foo", 1, {
 *     printf("Foo: %s\n", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_osiddddddiidddd(name, numreturns, wrapped_code) \
    LUA_EMBED_GEN(__script__##name, numreturns, \
        /* arg1 reserved for object */ \
        std::string arg2 = LuaEngine::getString(2); \
        int arg3 = LuaEngine::getInteger(3); \
        double arg4 = LuaEngine::getDouble(4); \
        double arg5 = LuaEngine::getDouble(5); \
        double arg6 = LuaEngine::getDouble(6); \
        double arg7 = LuaEngine::getDouble(7); \
        double arg8 = LuaEngine::getDouble(8); \
        double arg9 = LuaEngine::getDouble(9); \
        int arg10 = LuaEngine::getInteger(10); \
        int arg11 = LuaEngine::getInteger(11); \
        double arg12 = LuaEngine::getDouble(12); \
        double arg13 = LuaEngine::getDouble(13); \
        double arg14 = LuaEngine::getDouble(14); \
        double arg15 = LuaEngine::getDouble(15); \
        , wrapped_code)

