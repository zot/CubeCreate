import os

strings = [
    'i', 's', 'd', 'o', 'b',
    'ii', 'is', 'ss', 'sd', 'si', 'oi', 'ob', 'os', 'od', 'dd', 'ds', 'do', 'di',
    'iis', 'iii', 'iid', 'ddd', 'sdd', 'sss', 'dds', 'ssd', 'ssi', 'iss', 'sis',
    'oddd', 'dddd', 'iddd', 'iiss', 'iiis', 'ssdi', 'ssdd', 'iiii', 'iidd', 'isss', 'siis', 'ssss', 'ssds', 'ssis', 'sisi', 'siii', 'siii',
    'sdddi', 'sssdd', 'ddddi', 'sdddd', 'siidi', 'iiiss', 'iiisi', 'iiiii', 'idddd', 'iisss', 'isiss', 'ssdis', 'ssdds',
    'sdddii', 'dddddd', 'iidddi', 'iisddd', 'iiiddd', 'ddddii', 'idddsi', 'ssiiid', 'ddddid', 'iiiiii', 'sidddd',
    'sdddddd', 'ddddddd', 'iiiiddd', 'iiddddd', 'ssiiidi', 'iiiiiii', 'sddddid',
    'ddddddii', 'ddddiiid', 'iidddddd', 'ssiiiiii', 'siisdddd',
    'ddddddiii', 'oidddiiii', 'idddidddi', 'dddsiiidi', 'iiidddidii', 'ddddddiiid', 'dddiiiiii',
    'ddddddiiidi', 'osiddddddii', 'iiidddidiii', 'iissdddiiii', 'iiddddddidi', 'ddddddiiidii',
    'iiidddidiiibi', 'iiidddidiibibi', 'iiddddddidib', 'idddddddiiii', 'idddddiidddi',
    'dddddddiiidddd',
    'osiddddddiidddd'
]

out = open('script_engine_lua_generated.h', 'w')
for string in strings:
    out.write('''
/**
 * @def LUA_EMBED_%(string)s
 * @ingroup Lua_Engine_Group
 * @brief Wrapper over LUA_EMBED_GEN, accepting arguments %(string)s.
 * @param name Name of embedded lua function
 * @param numreturns Number of items the function returns onto stack
 * @param wrapped_code The code to wrap itself
 * 
 * THIS MACRO IS AUTO-GENERATED.\\n
 * -----------------------------\\n
 * This macro wraps over LUA_EMBED_GEN and sets up arguments - arg1 to argN of proper types.
 * Those can be later used. No need to pop them, it all happens automatically.
 * @code
 * LUA_EMBED_si(\"foo\", 1, {
 *     printf(\"Foo: %%s\\n\", arg1);
 *     LuaEngine::pushValue(arg2);
 * });
 * @endcode
 * @see LUA_EMBED_GEN()
 */
#define LUA_EMBED_%(string)s(name, numreturns, wrapped_code) \\
    LUA_EMBED_GEN(__script__##name, numreturns, \\
''' % { 'string': string })

    index = 0
    for param in string:
        out.write('        ')
        temp = { 'index': index, 'indexplus': index+1 }
        if param == 'i':
            out.write('_UNUSED_ int arg%(indexplus)d = LuaEngine::getInteger(%(indexplus)d); \\\n' % temp)
        elif param == 's':
            out.write('_UNUSED_ std::string arg%(indexplus)d = LuaEngine::getString(%(indexplus)d); \\\n' % temp)
        elif param == 'd':
            out.write('_UNUSED_ double arg%(indexplus)d = LuaEngine::getDouble(%(indexplus)d); \\\n' % temp)
        elif param == 'b':
            out.write('_UNUSED_ bool arg%(indexplus)d = LuaEngine::getBool(%(indexplus)d); \\\n' % temp)
        elif param == 'o':
            out.write('/* arg%(indexplus)d reserved for object */ \\\n' %temp)
        else:
            print 'Invalid parameter:', param
            assert(0)
        index += 1

    out.write('        , wrapped_code)\n\n')

out.close()

