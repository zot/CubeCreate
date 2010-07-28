#
# CMake for CubeCreate
# -------------------------
# this makes Google V8 library (scons build system replacement)
# reference from http://code.google.com/p/gamekit/source/browse/trunk/Dependencies/Source/V8/CMakeLists.txt

# determine architecture from cmake info. Supported architectures are arm, mips, x86, x86_64.
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set(CC_V8_ARCHITECTURE "arm")
else (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips")
        set(CC_V8_ARCHITECTURE "mips")
    else (${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips")
        if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "64")
            set(CC_V8_ARCHITECTURE "x64")
        else (${CMAKE_SYSTEM_PROCESSOR} MATCHES "64")
            set(CC_V8_ARCHITECTURE "ia32")
        endif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "64")
    endif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips")
endif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")

# default visibility = hidden

if (NOT DEFINED CC_V8_VISIBILITY)
    if (WIN32)
        set(CC_V8_VISIBILITY default)
    else (WIN32)
        set(CC_V8_VISIBILITY hidden)
    endif (WIN32)
endif (NOT DEFINED CC_V8_VISIBILITY)

# default regexp

if (NOT DEFINED CC_V8_REGEXP)
    set(CC_V8_REGEXP native)
endif (NOT DEFINED CC_V8_REGEXP)

# default cxxflags

set(CMAKE_CXX_FLAGS -O3)

if (NOT MSVC)
    add_definitions(-fomit-frame-pointer -fdata-sections -ffunction-sections)
endif (NOT MSVC)

if (MSVC)
    set(CMAKE_CXX_FLAGS /O2)
    add_definitions(/MT)
endif (MSVC)

# PLATFORM INDEPENDENT SOURCE FILES. Set them into separate variable.
set(CC_V8_INDEP
    src/accessors.cc
    src/allocation.cc
    src/api.cc
    src/assembler.cc
    src/ast.cc
    src/bootstrapper.cc
    src/builtins.cc
    src/checks.cc
    src/circular-queue.cc
    src/code-stubs.cc
    src/codegen.cc
    src/compilation-cache.cc
    src/compiler.cc
    src/contexts.cc
    src/conversions.cc
    src/counters.cc
    src/cpu-profiler.cc
    src/data-flow.cc
    src/dateparser.cc
    src/debug-agent.cc
    src/debug.cc
    src/disassembler.cc
    src/diy-fp.cc
    src/dtoa.cc
    src/execution.cc
    src/factory.cc
    src/flags.cc
    src/flow-graph.cc
    src/frame-element.cc
    src/frames.cc
    src/full-codegen.cc
    src/func-name-inferrer.cc
    src/global-handles.cc
    src/fast-dtoa.cc
    src/fixed-dtoa.cc
    src/handles.cc
    src/hashmap.cc
    src/heap-profiler.cc
    src/heap.cc
    src/ic.cc
    src/interpreter-irregexp.cc
    src/jsregexp.cc
    src/jump-target.cc
    src/liveedit.cc
    src/log-utils.cc
    src/log.cc
    src/mark-compact.cc
    src/messages.cc
    src/objects.cc
    src/oprofile-agent.cc
    src/parser.cc
    src/profile-generator.cc
    src/property.cc
    src/regexp-macro-assembler-irregexp.cc
    src/regexp-macro-assembler.cc
    src/regexp-stack.cc
    src/register-allocator.cc
    src/rewriter.cc
    src/runtime.cc
    src/scanner.cc
    src/scopeinfo.cc
    src/scopes.cc
    src/serialize.cc
    src/snapshot-common.cc
    src/spaces.cc
    src/string-stream.cc
    src/stub-cache.cc
    src/token.cc
    src/top.cc
    src/type-info.cc
    src/unicode.cc
    src/utils.cc
    src/v8-counters.cc
    src/v8.cc
    src/v8threads.cc
    src/variables.cc
    src/version.cc
    src/virtual-frame.cc
    src/vm-state.cc
    src/zone.cc
)

# JS library.
set(CC_V8_LIBRARY
    src/runtime.js
    src/v8natives.js
    src/array.js
    src/string.js
    src/uri.js
    src/math.js
    src/messages.js
    src/apinatives.js
    src/date.js
    src/regexp.js
    src/json.js
    src/liveedit-debugger.js
    src/mirror-debugger.js
    src/debug-debugger.js
)

# ARM dependent sources.
set(CC_V8_ARCH_ARM
    src/fast-codegen.cc
    src/jump-target-light.cc
    src/virtual-frame-light.cc
    src/arm/builtins-arm.cc
    src/arm/codegen-arm.cc
    src/arm/constants-arm.cc
    src/arm/cpu-arm.cc
    src/arm/debug-arm.cc
    src/arm/disasm-arm.cc
    src/arm/fast-codegen-arm.cc
    src/arm/frames-arm.cc
    src/arm/full-codegen-arm.cc
    src/arm/ic-arm.cc
    src/arm/jump-target-arm.cc
    src/arm/macro-assembler-arm.cc
    src/arm/regexp-macro-assembler-arm.cc
    src/arm/register-allocator-arm.cc
    src/arm/stub-cache-arm.cc
    src/arm/virtual-frame-arm.cc
    src/arm/assembler-arm.cc
)

# MIPS dependent sources
set(CC_V8_ARCH_MIPS
    src/fast-codegen.cc
    src/mips/assembler-mips.cc
    src/mips/builtins-mips.cc
    src/mips/codegen-mips.cc
    src/mips/constants-mips.cc
    src/mips/cpu-mips.cc
    src/mips/debug-mips.cc
    src/mips/disasm-mips.cc
    src/mips/fast-codegen-mips.cc
    src/mips/full-codegen-mips.cc
    src/mips/frames-mips.cc
    src/mips/ic-mips.cc
    src/mips/jump-target-mips.cc
    src/mips/macro-assembler-mips.cc
    src/mips/register-allocator-mips.cc
    src/mips/stub-cache-mips.cc
    src/mips/virtual-frame-mips.cc
)

# x86 dependent sources
set(CC_V8_ARCH_IA32
    src/jump-target-heavy.cc
    src/virtual-frame-heavy.cc
    src/ia32/assembler-ia32.cc
    src/ia32/builtins-ia32.cc
    src/ia32/codegen-ia32.cc
    src/ia32/cpu-ia32.cc
    src/ia32/debug-ia32.cc
    src/ia32/disasm-ia32.cc
    src/ia32/fast-codegen-ia32.cc
    src/ia32/frames-ia32.cc
    src/ia32/full-codegen-ia32.cc
    src/ia32/ic-ia32.cc
    src/ia32/jump-target-ia32.cc
    src/ia32/macro-assembler-ia32.cc
    src/ia32/regexp-macro-assembler-ia32.cc
    src/ia32/register-allocator-ia32.cc
    src/ia32/stub-cache-ia32.cc
    src/ia32/virtual-frame-ia32.cc
)

# x86_64 dependent sources
set(CC_V8_ARCH_X64
    src/fast-codegen.cc
    src/jump-target-heavy.cc
    src/virtual-frame-heavy.cc
    src/x64/assembler-x64.cc
    src/x64/builtins-x64.cc
    src/x64/codegen-x64.cc
    src/x64/cpu-x64.cc
    src/x64/debug-x64.cc
    src/x64/disasm-x64.cc
    src/x64/fast-codegen-x64.cc
    src/x64/frames-x64.cc
    src/x64/full-codegen-x64.cc
    src/x64/ic-x64.cc
    src/x64/jump-target-x64.cc
    src/x64/macro-assembler-x64.cc
    src/x64/regexp-macro-assembler-x64.cc
    src/x64/register-allocator-x64.cc
    src/x64/stub-cache-x64.cc
    src/x64/virtual-frame-x64.cc
)

# DTOA
set(CC_V8_DTOA
    src/dtoa-config.c
)

# snapshot
set(CC_V8_SNAPSHOT
    src/snapshot-empty.cc
)

# generated using python script from JS files (tools/generate_from_library.py)
set(CC_V8_GEN
    gen/libraries.cc
)

# put library into source group
source_group(library FILES ${CC_V8_LIBRARY})

# and create one var for full source. (except arch dep stuff, which is appeneded later)
set(CC_V8_FULL
    ${CC_V8_INDEP}
    ${CC_V8_LIBRARY}
    ${CC_V8_DTOA}
    ${CC_V8_SNAPSHOT}
    ${CC_V8_GEN}
)

#
# FLAGS SECTION
#

# add things into debug if debug target is set.
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DV8_ENABLE_CHECKS -DENABLE_DISASSEMBLER -D_DEBUG -DDEBUG)
    set(CC_V8_FULL ${CC_V8_FULL} src/objects-debug.cc src/prettyprinter.cc src/regexp-macro-assembler-tracer.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS -g -O0)
    endif (CMAKE_COMPILER_IS_GNUCXX)
    if (MSVC)
        set(CMAKE_CXX_FLAGS /Od /Gm)
    endif (MSVC)
endif (${CMAKE_BUILD_TYPE} MATCHES "Debug")

# some V8 parameters ported from scons.
if (${CC_V8_VMSTATE})
    add_definitions(-DENABLE_VMSTATE_TRACKING)
endif (${CC_V8_VMSTATE})

if (${CC_V8_PROTECTHEAP})
    add_definitions(-DENABLE_VMSTATE_TRACKING -DENABLE_HEAP_PROTECTION)
endif (${CC_V8_PROTECTHEAP})

if (${CC_V8_PROFILINGSUPPORT})
    add_definitions(-DENABLE_VMSTATE_TRACKING -DENABLE_LOGGING_AND_PROFILING)
endif (${CC_V8_PROFILINGSUPPORT})

if (${CC_V8_DEBUGGERSUPPORT})
    add_definitions(-DENABLE_DEBUGGER_SUPPORT)
endif (${CC_V8_DEBUGGERSUPPORT})

if (${CC_V8_REGEXP} STREQUAL "interpreted")
    add_definitions(-DV8_INTERPRETED_REGEXP)
endif (${CC_V8_REGEXP} STREQUAL "interpreted")

if (${CC_V8_OPROFILE})
    add_definitions(-DENABLE_OPROFILE_AGENT)
endif (${CC_V8_OPROFILE})

# ARCHITECTURE CHECKS

# x86 architecture
if (${CC_V8_ARCHITECTURE} STREQUAL "ia32")
    add_definitions(-DV8_TARGET_ARCH_IA32 -D_USE_32BIT_TIME_T)
    source_group(ia32 FILES ${CC_V8_ARCH_IA32})
    set(CC_V8_FULL ${CC_V8_FULL} ${CC_V8_ARCH_IA32})
endif (${CC_V8_ARCHITECTURE} STREQUAL "ia32")

# arm architecture
if (${CC_V8_ARCHITECTURE} STREQUAL "arm")
    add_definitions(-DV8_TARGET_ARCH_ARM)
    source_group(arm FILES ${CC_V8_ARCH_ARM})
    set(CC_V8_FULL ${CC_V8_FULL} ${CC_V8_ARCH_ARM})
    
    if (${CC_V8_UNALIGNEDACCESSES})
        add_definitions(-DCAN_USE_UNALIGNED_ACCESSES=1)
    else (${CC_V8_UNALIGNEDACCESSES})
        add_definitions(-DCAN_USE_UNALIGNED_ACCESSES=0)
    endif (${CC_V8_UNALIGNEDACCESSES})
    
    if (WIN32)
        set(CC_V8_FULL ${CC_V8_FULL} src/arm/simulator-arm.cc)
    endif (WIN32)
endif (${CC_V8_ARCHITECTURE} STREQUAL "arm")

# mips architecture
if (${CC_V8_ARCHITECTURE} STREQUAL "mips")
    add_definitions(-DV8_TARGET_ARCH_MIPS)
    source_group(mips FILES ${CC_V8_ARCH_MIPS})
    set(CC_V8_FULL ${CC_V8_FULL} ${CC_V8_ARCH_MIPS})
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-fno-inline -EL -mips32r2 -Wa,-mips32r2)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CC_V8_ARCHITECTURE} STREQUAL "mips")

# x86_64 architecture
if (${CC_V8_ARCHITECTURE} STREQUAL "x64")
    add_definitions(-DV8_TARGET_ARCH_X64)
    source_group(x64 FILES ${CC_V8_ARCH_X64})
    set(CC_V8_FULL ${CC_V8_FULL} ${CC_V8_ARCH_X64})
endif (${CC_V8_ARCHITECTURE} STREQUAL "x64")

# PLATFORM CHECKS

if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-freebsd.cc src/platform-posix.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-ansi)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")

if (${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-openbsd.cc src/platform-posix.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-ansi)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-linux.cc src/platform-posix.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-ansi)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-macos.cc src/platform-posix.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-ansi -mmacosx-version-min=10.4)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-solaris.cc src/platform-posix.cc)
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-ansi -D__C99FEATURES__)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")

if (WIN32)
    set(CC_V8_FULL ${CC_V8_FULL} src/platform-win32.cc)
    add_definitions(-DWIN32)
endif (WIN32)

if (MSVC)
    add_definitions(/W0 /GR- /Gy /W3 /WX /wd4355 /wd4800)
    add_definitions(/D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE)
    if (${CC_V8_ARCHITECTURE} STREQUAL "arm")
        add_definitions(/wd4996)
    endif (${CC_V8_ARCHITECTURE} STREQUAL "arm")
    if (${CC_V8_MSVC_VERBOSE_OFF})
        add_definitions(/nologo)
    endif (${CC_V8_MSVC_VERBOSE_OFF})
    if (${CC_V8_ENABLE_DISASSEMBLER})
        add_definitions(-DENABLE_DISASSEMBLER)
    endif (${CC_V8_ENABLE_DISASSEMBLER})
    # dtoa cflags
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} /WX /wd4018 /wd4244)
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-fno-rtti -fno-exceptions -fvisibility=${CC_V8_VISIBILITY} -Wall -W -Wno-unused-parameter -Wnon-virtual-dtor)
    if (WIN32)
        add_definitions(-pedantic -Wno-long-long)
    endif (WIN32)
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        add_definitions(-pedantic)
    endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        add_definitions(-pedantic)
    endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if (${CC_V8_ENABLE_DISASSEMBLER})
        add_definitions(-DENABLE_DISASSEMBLER)
    endif (${CC_V8_ENABLE_DISASSEMBLER})
    add_definitions(-Wno-uninitialized)
endif (CMAKE_COMPILER_IS_GNUCXX)

#
# CREATE LIBRARY
#

include_directories(src)
add_library(V8_${CC_BUILD_SUFFIX} ${CC_V8_FULL})

install(TARGETS V8_${CC_BUILD_SUFFIX}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
