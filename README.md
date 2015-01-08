# LC4-Binary-Interpreter

Design: This concept was created as an assignment by Professor Thomas Farmer at the University of Pennsylvania. .h files were provided. All implementation completed by Ryan Smith.

Overview: Program to investigate binary program files and print contents. (for lc4 micro-architecture) LC4 is a micro-architecture created by the University of Pennsylvania. This program was created with knowledge of the LC4 ISA. In interrogates LC4 binary files (.obj) and prints the contents in the form <LABEL><ADDRESS><CONTENTS><ASSEMBLY>.

This program operates by interrogating the file information in bit form and constructing a linked list. Each node of the linked list contains informatino pertaining to the label, address, contents, and assembly fields mentioned above.

Functions are provided for manipulating the linked list (search, add node, delete list/free memory, etc.)

Use: This program is executed from the command line. To use this program use the command "make all" from within the directory containing the Makefile. Then run the file "lc4" that is created. (on mac this is run with the command ./lc4) You will be prompted by the program to provide the file you would like to interrogate. Make sure to include the .obj extension in the file name.

Other Info: 3 sample .obj files are included for use in demonstrating this program. They are contained with the zip folder - Sample .obj files.zip.