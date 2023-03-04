@echo off

set BASE_DIRECTORY="%CD%\.."
setx YACKO_WORKING_DIRECTORY "%BASE_DIRECTORY%\assets"

cd ..\
.\imports\thirdparty\premake\premake5.exe --file=premake5.lua vs2022
cd scripts

PAUSE