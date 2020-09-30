@echo off

pushd ..\

set files[0]=""
set /a k=1

setlocal enabledelayedexpansion

for /r %%i in (*.h) do (
    
     set files[!k!] = %%i
     echo !k!
     set /a k+=1    
     
)

(for %%a in (%files%) do ( 
   echo %%a 
))
Rem start "" %~dp0HeaderTool.exe %files%


call vendor\bin\premake\premake5.exe vs2019
popd
PAUSE