REM este BAT solo sirve para DOS, con DJGPP+ALLEGRO 4
REM incluye los datos en el exe, y luego lo comprime
REM TODO : hacer un makefile para linux y windows, usar AlMake (otro de mis proyectos)
@echo off

gcc -s -Wall -O3 main.c -o ../bin/nachoblast.exe -lalleg

pause

exe2coff ..\bin\nachoblast.exe

copy /b C:\lenguaje\djgpp\bin\cwsdstub.exe + ..\bin\nachoblast  ..\bin\nachoblast.exe

exedat -c ..\bin\nachoblast.exe ..\dat\game.dat

upx --best ..\bin\nachoblast.exe

del ..\bin\nachoblast
