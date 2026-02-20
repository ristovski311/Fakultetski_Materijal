@echo off

REM ********   PODESAVANJA - MENJA STUDENT *********

set JCUP_HOME="C:\JCUP"
set JAVA_HOME="C:\Program Files\Java\jdk-23"
set PARSER_CLASS_NAME="MPParser"
set CUP_SPEC_NAME="MPParserError.cup"

REM ********   POZIV JAVA CUP APLIKACIJE  ***********

echo vrednost : %JCUP_HOME%
%JAVA_HOME%\bin\java -classpath %JCUP_HOME% java_cup.Main -parser %PARSER_CLASS_NAME% -symbols sym -dump < %CUP_SPEC_NAME%

PAUSE 