@echo off 

REM How to use this file
REM --------------------
REM Add the file CC.BAT for the Compiler setup RunFile making sure to check
REM the 'use other file' option. The just compile a file Alt-F10 to see the
REM result.

Echo + Example Batch Compile >> %2
Echo + ===================== >> %2
Echo +  >> %2
Echo + The file being compile is %1 >> %2
Echo + The error file to be generate is %2 >> %2
Echo + The file being compiled without extension is %3 >> %2
Echo +  >> %2
Echo + For example: >> %2
Echo + Compile file %1 to generate output file %2 >> %2
Echo +  >> %2
Echo + BCC +\work\zeus\zeus1.cfg -c %1 >> %2
Echo + >> %2
Echo + Refer to the file CC.BAT for more information or >> %2
Echo + look at the compile information in the online help.>> %2


REM The information above shows how the batch file is called. The information
REM below shows what your batch file should look like. (it only needs to be
REM one line long).
REM ProgramToRun [OPTIONS] %1 >> %2
REM Example: BCC +\work\zeus\zeus1.cfg -c %1 >> %2

REM To get Zeus to strip a error listing file you would add the following:
REM Strip [listing file] Error Warning > %2
REM For more information on using strip run strip ?

REM To make Zeus compile a file based on extension you would use the following:

REM Check if the file being compiled is a cpp file
REM IF %1 == %3.cpp
REM    BCC +\work\zeus\zeus1.cfg -c %1 >> %2
REM    GOTO exit
REM IF %1 == %3.asm
REM    tasm %1 >> %2
REM    GOTO exit
REM IF %1 == %3.mak
REM    make -f%1 >> %2
REM    GOTO exit
REM :exit
