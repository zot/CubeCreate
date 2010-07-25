SET OLD_PATH=%PATH%
SET PATH=windows\dll;Python26;C:\PYTHON26\;src\windows\sdl\lib;src\windows\sdl_image\lib;src\windows\sdl_mixer\lib;%PATH%

SET OLD_PYTHONHOME=%PYTHONHOME%
SET PYTHONHOME=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONHOME%

SET OLD_PYTHONPATH=%PYTHONPATH%
SET PYTHONPATH=Python26\lib;Python26\DLLs;C:\Python26\lib;C:\Python26\DLLs;%PYTHONPATH%

SET PREFIX="cbuild\src\server"
if exist %PREFIX%\CC_Server_Windows-%PROCESSOR_ARCHITECTURE%.exe
(
    %PREFIX%\CC_Server_Windows-%PROCESSOR_ARCHITECTURE%.exe %*
    echo "To save the output, add     > out_server 2>&1"
)
else
(
    echo "No executable exists for architecture %PROCESSOR_ARCHITECTURE%."
    SET PATH=%OLD_PATH%
    SET PYTHONHOME=%OLD_PYTHONHOME%
    SET PYTHONPATH=%OLD_PYTHONPATH%
    pause
    goto :end
)

SET PATH=%OLD_PATH%
SET PYTHONHOME=%OLD_PYTHONHOME%
SET PYTHONPATH=%OLD_PYTHONPATH%
