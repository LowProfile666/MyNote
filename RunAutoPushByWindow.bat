@echo off
REM 获取脚本当前所在目录
set SCRIPT_DIR=%~dp0
REM 将反斜杠替换为正斜杠
set SCRIPT_DIR=%SCRIPT_DIR:\=/%

REM 调用 Git Bash 并执行 AutoPush.sh 脚本
"D:\Git\bin\bash.exe" -c "sh %SCRIPT_DIR%AutoPushByWindow.sh"