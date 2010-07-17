SET OLD_PATH=%PATH%
SET PATH=windows\dll;Python26;C:\PYTHON26\;src\windows\sdl\lib;src\windows\sdl_image\lib;src\windows\sdl_mixer\lib;%PATH%

SET OLD_PYTHONHOME=%PYTHONHOME%
SET PYTHONHOME=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONHOME%

SET OLD_PYTHONPATH=%PYTHONPATH%
SET PYTHONPATH=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONPATH%

if "%PROCESSOR_ARCHITECTURE%" == "x86"
(
    SET ccarch=32
)
else
(
    SET ccarch=64
)

@echo off
for %exe in (bin\cc_client*.exe) do
(
    echo %exe | find %ccarch%
    if errorlevel 0
    (
        SET ccexec=%exe
    )
)
@echo on

if defined ccexec
(
    bin\%ccexec% %* -r > out_client 2>&1
)
else
(
    echo "No executable exists for architecture %ccarch%."
    SET PATH=%OLD_PATH%
    SET PYTHONHOME=%OLD_PYTHONHOME%
    SET PYTHONPATH=%OLD_PYTHONPATH%
    pause
    goto :end
)

echo "(If a problem occurred, look in out_client)"

pause

SET PATH=%OLD_PATH%
SET PYTHONHOME=%OLD_PYTHONHOME%
SET PYTHONPATH=%OLD_PYTHONPATH%
