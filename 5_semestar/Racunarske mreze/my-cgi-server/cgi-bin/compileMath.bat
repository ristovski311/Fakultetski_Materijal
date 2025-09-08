@echo off
echo Compiling hello.cpp into greeting.cgi...

g++ C:\my-cgi-server\cgi-bin\math.cpp -o C:\my-cgi-server\cgi-bin\math.cgi

if %errorlevel% neq 0 (
    echo Compilation failed.
	pause
    exit /b %errorlevel%
)

echo Compilation successful. Output: greeting.cgi

pause