@echo off
echo Setting Up Developer Environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
SET Platform=
echo Building RayX
msbuild /m /p:PlatformTarget=x86 /p:Configuration=Debug RayX.sln
pause
echo on
cls