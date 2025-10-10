echo off

rem Cmake variables
set visualStudioVersion=16
set generatorName="Visual Studio 16 2019"
rem Win32/x64
set targetArchitectureAndModel=Win32

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

cmake -B %builDirectory% -G %generatorName% -A %targetArchitectureAndModel% --loglevel=%logLevel% -DBUILD_SHARED_LIBS=!buildShared! -DBUILD_UNIT_TESTS=!buildTests!

echo "*********************************************"
echo "           Building Project Ended!           "
echo "*********************************************"

cd %originalDir%

set /p DUMMY=Hit ENTER to finish...