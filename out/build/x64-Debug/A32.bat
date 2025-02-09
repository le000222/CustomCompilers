:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A32 - CST8152 - Fall 2022

CLS
SET COMPILER=RidCompiler.exe

SET FILE=INPUTA32

SET ASSIGNMENT=A32
SET EXTENSION=de
SET OUTPUT=out
SET ERROR=err

SET PARAM=P

:: ---------------------------------------------------------------------
:: Begin of Tests (A12 - F22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off
ECHO " ____________________________________ "
ECHO "|                                    |"
ECHO "|  ....... 'RID' LANGUAGE ........   |"
ECHO "|    _____    _______    _____       |"
ECHO "|   ||   \\    || ||    ||    \\     |"
ECHO "|   ||    \\   || ||    ||     \\    |"
ECHO "|   || ___//   || ||    ||      \\   |"
ECHO "|   ||  \\     || ||    ||      //   |"
ECHO "|   ||   \\    || ||    ||     //    |"
ECHO "| __||__  \\___||_||____||____//     |"
ECHO "|                                    |"
ECHO "|  .. ALGONQUIN COLLEGE - 2022F ..   |"
ECHO "|____________________________________|"
ECHO "                                   "
ECHO "[READER SCRIPT ...................]"
ECHO "                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A32 - F22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE%.%EXTENSION%	> %FILE%-%ASSIGNMENT%.%OUTPUT%	2> %FILE%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A32 - F22) --------------------------------------------
:: ---------------------------------------------------------------------
