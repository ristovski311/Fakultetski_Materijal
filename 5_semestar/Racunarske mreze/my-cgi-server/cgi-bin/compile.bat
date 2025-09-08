@echo off
echo Compiling hello.cpp into greeting.cgi...

g++ C:\my-cgi-server\cgi-bin\hello.cpp -o C:\my-cgi-server\cgi-bin\greeting.cgi

if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

echo Compilation successful. Output: greeting.cgi

pause