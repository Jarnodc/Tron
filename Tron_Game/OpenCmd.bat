@echo off
set loop=0
:loop
	type something.txt
set /a loop=%loop%+1 
if "%loop%"=="5" goto next
goto loop

:next
exit