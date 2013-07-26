@echo off

set CURPATH=C:\liuzp\dev\OpenCLProject

cd %CURPATH%
del /S /F /Q *.ncb *sdf
rd /S /Q %CURPATH%\Debug 

cd %CURPATH%\Test 
rd /S /Q Debug
del /S /F /Q *.ncb *sdf

cd %CURPATH%\MatrixVectorMultiply
rd /S /Q Debug
del /S /F /Q *.ncb *sdf