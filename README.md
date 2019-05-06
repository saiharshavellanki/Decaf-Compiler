**Structure**

1. scanner.l is the scanner file which contains information regarding different type of tokens
2. parser.y is the parser file which contains grammar
3. classes.h is header file which contains information about all the classes in AST.Classes are implemented using visitor design pattern
4. classes.cpp contains functions which are used for traversing in AST
5. Makefile contains instructions for compiling the code
6. test-programs directory contains sample .dcf codes

**Run**

To compile the code use make command which produces an executable ./ast 
Compilation sequence <br/>
Step 1: flex scanner.l : Tokenises input program <br/>
Step 2: bison -d parser.y : Constructions parse tree and does syntax analysis <br/>
Step 3: g++ -w -g -std=c++11 parser.tab.c  classes.cpp -lfl -ltinfo -lpthread -ldl -o ast : Constructs AST and does semantic analysis <br/>

To run the code take .dcf file as input to ./ast (Example : ./ast < test-programs/hanoi.dcf)

**Things Implemented :**
Scanner,Parser,AST Construction,Semantic Checking

**Things Remaining:**
LLVM IR Generation
