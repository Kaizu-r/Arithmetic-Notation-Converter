# C++ Arithmetic Notation Converter

The C++ Arithmetic Notation Converter is a program whose purpose is to convert a given arithmetic notation between three different arithmetic notations: infix, prefix, and postfix notations.

## How to Run the Program

To run the program:

* Open the Command Prompt or any CLI (Command Line Interface)
* Move to the file directory containing the program, for example:
    * cd Projects/Arithmetic-Notation-Converter
* Use the following command:
    * ./program {arg1} {arg2} {string} [-e]

ARGUMENTS GUIDE
* {arg1} and {arg2} (NOTE: order of arguments MATTER):
    * -in   -pre     -> Infix to Prefix
    * -pre  -in      -> Prefix to Infix
    * -pos  -pre     -> Postfix to Prefix
    * -pre  -pos     -> Prefix to Postfix
    * -in   -pos     -> Infix to Postfix
    * -pos  -in      -> Postfix to Infix

* {string}           : The expression to be OPERATED

* [-e]               : [Optional Argument] Emphasize output, (converts ouput to UPPERCASE)

## Programming Language Used and Dependencies Utilized

The program is written entirely in C++, with the following dependencies used in the program:
* stdlib.h : 
* iostream : 

## Program Features

* Use of Structures (structs) to build the binary tree data structure
    * structs were used instead of classes to lessen the program's complexity