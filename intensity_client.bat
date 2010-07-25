SET OLD_PATH=%PATH%
SET PATH=windows\dll;Python26;C:\PYTHON26\;src\windows\sdl\lib;src\windows\sdl_image\lib;src\windows\sdl_mixer\lib;%PATH%

SET OLD_PYTHONHOME=%PYTHONHOME%
SET PYTHONHOME=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONHOME%

SET OLD_PYTHONPATH=%PYTHONPATH%
SET PYTHONPATH=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONPATH%

SET PREFIX="cbuild\src\client"
if exist %PREFIX%\CC_Client_Windows-%PROCESSOR_ARCHITECTURE%.exe
(
    %PREFIX%\CC_Client_Windows-%PROCESSOR_ARCHITECTURE%.exe %* -r > out_client 2>&1
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
