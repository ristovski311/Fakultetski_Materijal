@echo off
echo Compiling hello.cpp into greeting.cgi...

g++ "C:\gitHub\Fakultetski_Materijal\5_semestar\Racunarske mreze\my-cgi-server\cgi-bin\test.cpp" -o "C:\gitHub\Fakultetski_Materijal\5_semestar\Racunarske mreze\my-cgi-server\cgi-bin\test.cgi"

if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

echo Compilation successful. Output: greeting.cgi

pause