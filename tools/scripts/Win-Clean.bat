@echo off
pushd %~dp0\..\..\
call tools\bin-win\premake5.exe clean
popd
PAUSE
