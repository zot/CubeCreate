
Compiling CubeCreate
********************

The CubeCreate Engine officially supports Windows and Linux. Compilation
instructions for the two platforms have some shared aspects and
some non-shared aspects.

Shared
======

1. In both cases you should get the source code, either a zip file/tarball
   with a release, or straight from the source code repository, in which
   case you can simply do::

       git clone git://github.com/quaker66/CubeCreate.git

   You need the Git version control system installed. You can get it at `git-scm.com <http://git-scm.com/>`_.


Windows
-------

1. Get SCons from www.scons.org.
2. Get CMake from www.cmake.org.
3. Get Python from www.python.org. **Note:** The batch files etc. assume
   you are using Python 2.6.x.

In the directory where the source code was placed (usually 'CubeCreate'),
run (in a DOS shell, that is, inside cmd.exe) the following commands. They
assume you are building with Visual Studio Express 2008.

First, build V8 by going to src\thirdparty\v8 and running::

    scons mode=release env="INCLUDE:C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include;C:\Program Files\Microsoft Visual Studio 9.0\VC\Include;,LIB:C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib;C:\Program Files\Microsoft Visual Studio 9.0\VC\Lib;"

(change the path to point to where you have the Windows platform SDKs).

Then, go back up and to \cbuild, and there run::

    SET PATH=%PATH%;C:\Program Files\Microsoft Visual Studio 9.0\VC\bin;C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE
    cmake -G "Visual Studio 9 2008" ..

This should create a project file for VC++, which you can then build. Note
that the first line gets the VC++ compiler in your path; if it is already
there, or in a different location, change or remove that line accordingly.

You can then open the generated solution file in Visual Studio. In
Build->Configuration Manager make sure you are compiling for 'Release'
and not 'Debug', and then start the build.


Linux
-----

The following explains how to install on Ubuntu (9.10). We welcome
feedback about your experience in other distros, so we can add it to this file.
In general, in other distros (or versions of Ubuntu) there might be minor changes
to the package names and so forth, but overall, things should be similar.

First, install Git, CMake, SCons and other important stuff:

  Ubuntu 9.10::

     sudo apt-get install git-core cmake scons g++ libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev python-dev zlib1g-dev

Go to the V8 directory, ./src/thirdparty/v8, and run::

    GCC_VERSION="44" scons

there. Then go back down to the base dir, and enter the directory 'cbuild', and run::

    cmake ..

this should configure things correctly. Then run::

    make

