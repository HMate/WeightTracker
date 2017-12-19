@echo off
echo "Copying SFML dlls to %1"
copy /Y %SFML_LIB_PATH%\sfml-*-2.dll %1