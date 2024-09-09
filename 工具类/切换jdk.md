# 使用bat程序

```bat
@echo off
setlocal

REM Define JDK paths
set "JDK8_PATH=D:\Java\jdk-8"
set "JDK17_PATH=D:\Java\jdk-17"
set "JDK21_PATH=D:\Java\jdk-21"

REM Ask for JDK version
set /p JDK_VERSION="Enter JDK version (8, 17, 21): "

REM Set JAVA_HOME based on user input
if "%JDK_VERSION%"=="8" (
    set "NEW_JAVA_HOME=%JDK8_PATH%"
) else if "%JDK_VERSION%"=="17" (
    set "NEW_JAVA_HOME=%JDK17_PATH%"
) else if "%JDK_VERSION%"=="21" (
    set "NEW_JAVA_HOME=%JDK21_PATH%"
) else (
    echo Invalid JDK version. Exiting...
    exit /b 1
)

REM Set JAVA_HOME environment variable
setx /M JAVA_HOME "%NEW_JAVA_HOME%"
echo JAVA_HOME is set to %NEW_JAVA_HOME%

endlocal
```

主要是 setx 命令可以向全局变量中写入值，set 命令只在当前有效。

将该 bat 程序的路径载入path环境变量中，就可以全局访问了。