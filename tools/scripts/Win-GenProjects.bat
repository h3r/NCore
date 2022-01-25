@echo off
pushd %~dp0\..\..\
call tools\bin-win\premake5.exe vs2022
popd
PAUSE
