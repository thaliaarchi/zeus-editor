REM How to use this file
REM ====================

REM Add the file 'c:\zeus200\zexample\CC.BAT' to the Compiler setup RunFile 
REM making sure to check the 'Use other file' option. Then just compile any 
REM file using the Alt-F10 command to see the results.

Echo . Example Batch Compile > %2
Echo . ===================== >> %2
Echo . >> %2
Echo . Below is the description of the batch file arguments:  >> %2
Echo . >> %2
Echo . The file being compiled is '%1' (argument #1) >> %2
Echo . The error file to be generated is '%2' (argument #2) >> %2
Echo . The file being compiled without extension is '%3' (argument #3) >> %2
Echo . >> %2
Echo . For example we are now compiling the file '%1' to generate the   >> %2
Echo . error output file '%2' and could possibly do this using the      >> %2
Echo . following batch file (Borland example) >> %2
Echo . >> %2
Echo . BCC +c:\work\zeus\zeus1.cfg -c %1 >> %2
Echo . >> %2
Echo . For more information on how to configure the compiler support refer    >> %2
Echo . to the section 'Setting up the Compiler' in the online help. For an    >> %2
Echo . example of typical batch files edit the 'CC.BAT' and copy the examples >> %2
Echo . given at the end of this file.                                         >> %2

GOTO exit

Information on Writing Batch Files for Zeus
===========================================

The information below shows what your batch file should look like. In
some cases your batch file may only need to be one line long and has 
the following format.

      ProgramToRun [OPTIONS] %1 >> %2

The command line is made up of the following parts:

      ProgramToRun - Your compiler full path and filename goes here
      [OPTIONS]    - Any options required by the ProgramToRun
      %1 >> %2    - File and pipe information supplied by Zeus
   
As an example here is a batch file for the Borland C++ compiler:

      BCC +c:\work\zeus\zeus1.cfg -c %1 >> %2

To get Zeus to strip a error listing file into an errors only file you would
have a batch file that looks like this:

      REM Run the compiler to produce a listing file
      ProgramToRun [OPTIONS] %1

      REM Take the listing file and generate a Zeus error file 
      Strip [listing file] Error Warning > %2

In this case the [listing file] is the output listing file created by your
compiler. For more information on using strip run Strip ?

Sample of how to Write an Extension Sensitive Compile
=====================================================

To make Zeus compile a file based on extension you would use a batch
file simular to the one shown below.

    @echo off
    
    REM ------------------------------------------------------------
    REM These give you an idea on what gets passed to the batch file
    REM ------------------------------------------------------------
    
    echo Argument #1) %1
    echo Argument #2) %2
    echo Argument #3) %3
    
    REM -------------------------
    REM See if we have a CPP file
    REM -------------------------
    
    IF NOT %1 == %3.cpp GOTO MAKE
       CL @C:\ZEUS\ZEUS.RSP -c %1 >> %2
       GOTO exit
    
    REM -------------------------
    REM See if we have a MAK file
    REM -------------------------
    
    :MAKE
    
    IF NOT %1 == %3.mak GOTO ERROR
       nmake -f%1 >> %2
       GOTO exit
    
    REM -------------------
    REM Unknown file format
    REM -------------------
    
    :ERROR
    
    echo Error compiling file '%1' as this file extension is not supported! > %2
    
    :exit
    
    REM --------------------------------------------------------------
    REM Add this pause and set the visible state to normal if you are
    REM having trouble getting this stuff to work.
    REM --------------------------------------------------------------
    
    REM pause
