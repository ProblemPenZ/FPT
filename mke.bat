cd .\

move .\build\Makefile .\src

xcopy .\res .\src /E /H /C /I

xcopy .\res .\build\exec/E /H /C /I

cd .\src\

mingw32-make.exe

cd ..\

move .\src\main.exe .\build\exec\

move .\src\Makefile .\build\

cd .\build\exec\

pause

cd ..\..\src

rmdir /s /q res

cd ..\build\exec

rmdir /s /q res
