@echo off

gcc -s -Wall -O3 main.c -o ../bin/nachoblast.exe -lalleg

pause

exe2coff ..\bin\nachoblast.exe

copy /b C:\lenguaje\djgpp\bin\cwsdstub.exe + ..\bin\nachoblast  ..\bin\nachoblast.exe

exedat -c ..\bin\nachoblast.exe ..\dat\game.dat

upx --best ..\bin\nachoblast.exe

del ..\bin\nachoblast
