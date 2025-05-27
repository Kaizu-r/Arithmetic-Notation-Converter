# Arithmetic Notation Converter

The Arithmetic Notation Converter is a program whose purpose is to convert a given arithmetic notation between three different arithmetic notations: infix, prefix, and postfix notations.

## How to Run the Program

To run the program:

* Open the Command Prompt or any CLI (Command Line Interface)
* Move to the file directory containing the program, for example:
    * cd /Arithmetic-Notation-Converter
* Use the following command:
    * ./program <arg1> <arg2> <string> [-e]

Arguments Guide
* <arg1> and <arg2> (NOTE: order of arguments MATTER):
    * -in   -pre     -> Infix to Prefix
    * -pre  -in      -> Prefix to Infix
    * -pos  -pre     -> Postfix to Prefix
    * -pre  -pos     -> Prefix to Postfix
    * -in   -pos     -> Infix to Postfix
    * -pos  -in      -> Postfix to Infix

* <string>           : The expression to be OPERATED

* [-e]               : [Optional Argument] Emphasize output, (converts ouput to UPPERCASE)