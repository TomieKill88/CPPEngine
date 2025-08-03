echo off

rem Cmake variables
set visualStudioVersion=16
set generatorName="Visual Studio 16 2019"
set targetProcessorArchitecture=x86

rem CMAKE Options
set buildShared=false
set buildTests=false
set logLevel=DEBUG

rem Directories
set originalDir=%cd%
set builDirectory="..\build"

cd..\source

echo "*********************************************"
echo "              Building Project               "
echo "*********************************************" 

cmake -B %builDirectory% -G %generatorName% --loglevel=%logLevel% -DBUILD_SHARED_LIBS=!buildShared!

echo "*********************************************"
echo "           Building Project Ended!           "
echo "*********************************************"

cd %originalDir%

set /p DUMMY=Hit ENTER to finish...