@echo off

set CURPATH=C:\liuzp\dev\OpenCLProject

del /S /F /Q *.ncb *sdf
rd /S /Q %CURPATH%\Debug 

cd %CURPATH%\Test 
rd /S /Q Debug

cd %CURPATH%\MatrixVectorMultiply
rd /S /Q Debug