# C++ Arithmetic Notation Converter

The C++ Arithmetic Notation Converter is a program whose purpose is to convert a given arithmetic notation between three different arithmetic notations: infix, prefix, and postfix notations.

# Installation Guide

**For Windows**
* Download then extract the Repository
* Install a C++ Compiler
    * Watch this [video](https://www.youtube.com/watch?v=oC69vlWofJQ) for instructions on how to install the compiler
* Set up the Environment Variables 
    * Go to the Windows Search Bar, type "edit the system environment variables" then open
    * Click "Environment Variables"
    * Inside the User Variables, click "Path" then click "Edit..."
    * Click New then click on Browse
    * Find the folder where the Repository is located
    * Once done, click OK, then close all windows

**For Linux**
* Download then extract the Repository
* Install a C++ Compiler by running the following commands
    * sudo apt install mingw-w64 (for Ubuntu distros)
* Set up PATH to recognized the program
    * Open the Terminal
    * Run this command
        export PATH= /yourfilepath :$PATH

# How to Run the Program

To run the program:

* Open the Terminal or Command Prompt
* Move to the file path containing the program, for example:
    * cd Projects/Arithmetic-Notation-Converter
* Compile converter.cpp by typing the following command
    * *g++ converter.cpp -o converter*
* Run the program by typing the following command:
    * *converter --from {arg1} --to {arg2} {string} [-e]*

## Arguments Guide
* {arg1} and {arg2} (NOTE: order of arguments MATTER):
    * infix    prefix     -> Infix to Prefix
    * prefix   infix      -> Prefix to Infix
    * postfix  prefix     -> Postfix to Prefix
    * prefix   postfix    -> Prefix to Postfix
    * infix    postfix    -> Infix to Postfix
    * postfix  infix      -> Postfix to Infix

* {string}           : The expression to be OPERATED

* [-e]               : [Optional Argument] Evaluates the expression

# Programming Language Used and Dependencies Utilized

The program is written entirely in C++, with the following dependencies used:
* stdlib.h 
* iostream 

# Program Features

* Use of Structures (structs) to build the binary tree data structure
    * structs were used instead of classes to lessen the program's complexity
* Tokenizer for turning input string to individual tokens. 
    * optional spaces for infix notation
* Parser/Syntax checker for each notation to check the validity of the input string
    * uses recursive descent where each production is its own function
* Evaluation of given string
    * uses stacks to evaluate the expression and auto-detects any math errors (division by zero)