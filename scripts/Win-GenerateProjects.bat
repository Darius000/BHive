@echo off

pushd ..\

Rem set files[0]=""
Rem set /a k=1

Rem setlocal enabledelayedexpansion

Rem for /r %%i in (*.h) do (
Rem     
Rem      set files[!k!] = %%i
Rem      echo !k!
Rem      set /a k+=1    
Rem      
Rem )
Rem 
Rem (for %%a in (%files%) do ( 
Rem    echo %%a 
Rem ))
Rem start "" %~dp0HeaderTool.exe %files%


call vendor\bin\premake\premake5.exe vs2019
popd
PAUSE