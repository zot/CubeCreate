
Compiling CubeCreate
********************

Officially supported platforms for CubeCreate (those which include binaries) are currently Linux and Windows.

It should work without problems also on Solaris, BSD and other UNIX-like or UNIX systems (official support will be added when we get bins).

Mac OS X support should be present too, with possibility to generate xcode project from cmake or build directly. (untested yet)

For different platforms, compilation instructions might differ a bit, so separate OSes will be explained separately.

For all OSes
============

1. In all cases, you need to get source code. 
   You can use either release tarball or Git source versioning system to get source code.
   (Git will get you most recent source)

   To get source from Git, use:

   .. code-block :: bash

       $ git clone git://github.com/quaker66/CubeCreate.git

   It assumes you have Git installed. (http://git-scm.com).
   If you're using Windows, you can use TortoiseGit GUI to make download easier.

Linux, BSD, Solaris and other UNIX-like or UNIX systems (excluding Darwin)
==========================================================================

On these OSes compilation should be really trivial.
Instructions assume Linux with deb packaging system,
with little modifications it should work everywhere.

1. Open terminal window and get some dependencies to build.

   .. code-block :: bash

       $ sudo apt-get install cmake build-essential libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev python-dev zlib1g-dev

   If I list the dependencies (for other OSes), they are:

   1. CMake - http://cmake.org - this is a build system.
   2. build-essential - on Debian, metapackage installing GNU compiler set and a few other things.
      Basically basic things you need to build sources.
   3. SDL dev package, SDL_image dev package, SDL_mixer dev package
   4. Python dev libraries and headers
   5. Zlib dev libraries and headers

2. Open a terminal, build CC:

   .. code-block :: bash

       $ cd $HOME/cubecreate_source/cbuild
       $ cmake ..
       $ make
       $ make install

   If you have a dualcore processor, you can use -j2 as make argument.

   If you want to build an experimental webbrowser plugin, provide -DINTENSITY_PLUGIN=1 as cmake argument.

   See more info about webbrowser plugin at the end of this page.

3. You're done, you should have binaries in CCROOT/bin and libraries in CCROOT/lib.

Windows
=======

On Windows, you don't need to get many dependencies, since most of them is already provided with CC.
If you have 64bit windows, get 32bit versions of dependencies, 64bit builds of CC are not yet supported on Windows.

You need to get:

1. CMake from www.cmake.org. Install it into standard directory. Let it write PATH variable when installing so it works correctly.
2. Python from www.python.org. **Note:** The batch files etc. assume
   you are using Python 2.6.x, so get 2.6.X release (currently 2.6.5 - http://python.org/download/releases/2.6.5/ , CC will be updated to latest soon)
   Install it into C:\\Python26 as usual and install it for ALL USERS.
   After installing, run Control panel of Windows, edit environment variables of system and append this into PATH:

   .. code-block :: bash

       ;C:\Python26;C:\Python26\Scripts

Then, you have two ways to build CC. Visual Studio Express Edition is recommended and Code::Blocks support is currently incomplete.

Using Visual Studio Express Edition
-----------------------------------

This is an easier and more straightforward version. Also, mingw build doesn't work correctly yet
(builds, links, but there are runtime errors)

1. Get Microsoft Visual Studio 2008 Express Edition from Microsoft website. CC works just with 2008 now.

   You don't need to install optional components, and install it into default path it tells you.

2. Run CMake GUI. As "Where is source code", set path to your CC directory. As "Where to build binaries",
   set cbuild directory of your CC directory.

   Hit "Configure" button. It will ask you what type of build files it should generate.
   Select MS Visual Studio 9 project. Don't set x64 even if you have 64bit OS.

   You'll see some variables in red. Set CMAKE_INSTALL_PREFIX to same value as "Where is source code" is.
   Hit Configure once again, and Generate.

3. Double-click CubeCreate.sln file in CCROOT\\cbuild, it'll open solution in MS Visual C++.

4. Right-click solution CubeCreate, select Properties, if active Configuration is Debug,
   click Configuration Properties on the left, run Configuration Manager on the top, set active
   Configuration to Release. Then, in those solution properties, in Configuration category, check "Build" checkbox for
   INSTALL project, and click Apply and close properties.

5. Press F7, it'll build solution. After successful build, you should get binaries into bin/ and libraries into lib/

Using MinGW and Code::Blocks
----------------------------

**Note:** it compiles and links, but has run-time errors atm.

1. Get MinGW from `sourceforge <http://sourceforge.net/projects/mingw/files/Automated MinGW Installer/MinGW 5.1.6/MinGW-5.1.6.exe/download>`_ and install it.
   Choose "Download and install", then "Candidate", let it install to for example C:\\mingw.

2. Append this into your PATH (as you did with python)

   .. code-block :: bash

       ;C:\mingw\bin

**MinGW compilation**

1. Run CMake GUI. As "Where is source code", set path to your CC directory. As "Where to build binaries",
   set cbuild directory of your CC directory.

   Hit "Configure" button. It will ask you what type of build files it should generate.
   Select MinGW Makefiles.

   You'll see some variables in red. Set CMAKE_INSTALL_PREFIX to same value as "Where is source code" is.

   Hit Configure once again, and Generate.

2. Run a command prompt, and "cd" into your CCROOT\\cbuild. Then run:

   .. code-block :: bash

       $ mingw32-make

   and wait until it finishes.

3. Run

   .. code-block :: bash

       $ mingw32-make install

   in the same command prompt in cbuild and you'll get binaries,

**Code::Blocks compilation**

1. Get latest Code::Blocks from website, install it,
   don't let it install mingw as you already have it in C:\\mingw.

2. Run CMake GUI. As "Where is source code", set path to your CC directory. As "Where to build binaries",
   set cbuild directory of your CC directory.

   Hit "Configure" button. It will ask you what type of build files it should generate.
   Select CodeBlocks MinGW Makefiles.

   You'll see some variables in red. Set CMAKE_INSTALL_PREFIX to same value as "Where is source code" is.

   If CMAKE_CODEBLOCKS_EXECUTABLE is not found, specify path to codeblocks.exe
   ("C:\\Program Files\\CodeBlocks\\codeblocks.exe", usually, on 64bit, it's "C:\\Program Files (x86)\\CodeBlocks\\codeblocks.exe")

   Hit Configure once again, and Generate.

3. Navigate into CCROOT\\cbuild in your file manager, open the cbp file using Code::Blocks.

4. Press CTRL+F9 in Code::Blocks to start build.
   When it finishes, select "Build target" on toolbar to "install",
   and press CTRL+F9 again to install it.

   Then, you'll have binaries in CCROOT\\bin and libraries in CCROOT\\lib.

