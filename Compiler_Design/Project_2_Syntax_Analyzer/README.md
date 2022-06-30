# Compiler Design Project 2: Syntax Analyzer

## Author Information

CCU CSIE 3B

408410120

鍾博丞

## Environment

ANTLR 4.9.3 is used in this project. Makefile will download `antlr-4.9.3-complete.jar` using `wget` automatically if it doesn't exist in the project directory.



## Makefile / Execution

You can simply compile and run this project with the command below:

`make run <filename>`, which is same as `java -cp ./antlr-4.9.3-complete.jar:. testParser <filename>`

Furthermore, if you want to draw the parsing table of the given file, you can type:

`make draw <filename>`, which is same as `java -cp ./antlr-4.9.3-complete.jar:. org.antlr.v4.gui.TestRig myparser translationUnit -gui <filename>`



## Standard of the CFG

The context-free grammar of this project is cited from the reference below

https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

https://gist.github.com/codebrainz/2933703



## No Preprocessor is Included

Thus, the declaration such as `#define`, `#include`, `#line`, `#undef`, `#error`, `#pragma`, `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif`, etc, is not declared in this project.

The types defined in another files or libraries, `uint8_t`, for example, can not be parsed correctly in this project.



## Some Pattern If TRACEON

The statements enumerated below will be printed in console when the parser detects these statements if `boolean TRACEON = true;`

1. Function definition
2. Declaration
3. printf(...);
4. Selection statement: if-else, switch-case
5. Iteration statement: while, do-while, for (ANSI/GNU C99)

You can declare a variable in `for` statement in GNU C99, but not in ANSI C

```
for (int i = 0; i < 10; ++i) continue;  // GNU C99
int i; for (i = 0; i < 10; ++i) continue;  // ANSI C
```

