@echo off

set FILETYPES=*.hpp *.cpp

cd ../Source
findstr -s -n -i -l "TODO" %FILETYPES%

cd ../Include
findstr -s -n -i -l "TODO" %FILETYPES%

pause