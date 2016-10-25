@echo off


maze.exe
IF ERRORLEVEL 1 GOTO err

maze.exe Correct
IF ERRORLEVEL 1 GOTO err

maze.exe Correct.txt
IF ERRORLEVEL 1 GOTO err

maze.exe withoutA.txt output.txt
IF ERRORLEVEL 1 GOTO err

maze.exe 2A.txt output.txt
IF ERRORLEVEL 1 GOTO err

maze.exe empty.txt output.txt
IF ERRORLEVEL 1 GOTO err

maze.exe Correct.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt aCorrect.txt
IF ERRORLEVEL 1 GOTO err

maze.exe Correct2.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt aCorrect2.txt
IF ERRORLEVEL 1 GOTO err

maze.exe noWay.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt aNoWay.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
Pause
EXIT /b

:err
ECHO Program testing failed :-(
Pause
EXIT /b