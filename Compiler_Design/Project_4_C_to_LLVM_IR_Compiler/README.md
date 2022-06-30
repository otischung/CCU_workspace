# Compiler Design Project 4: C\-to\-LLVM IR compiler

## Author Information

CCU CSIE 3B

408410120

鍾博丞

## Environment

ANTLR 4.9.3 is used in this project. Makefile will download `antlr-4.9.3-complete.jar` using `wget` automatically if it doesn't exist in the project directory.



## Makefile / Execution

You can simply compile and run this project with the command below:

`make run <filename>`, which is same as `java -cp ./antlr-4.9.3-complete.jar:. myCompiler_test <filename>`

Furthermore, if you want to draw the parsing table of the given file, you can type:

`make draw <filename>`, which is same as `java -cp ./antlr-4.9.3-complete.jar:. org.antlr.v4.gui.TestRig myCompiler translationUnit -gui <filename>`



Note that **`-s` option is the silent operation for Makefile**. As the flag is set, makefile doesn't print the commands as they are executed and thus you can get **pure LLVM IR pseudo assembly code**.

Therefore, run the command below will get **pure LLVM IR pseudo assembly code** :

```bash
make -s run filename.c >! filename.ll
```

Then, you can use `lli` to execute the code directly.

```bash
lli filename.ll
```

Another option is use  `llc` compiler to compile the code to assembly code. Then call `clang` or `gcc` to generate target code.

```bash
llc filename.ll
gcc filename.s -o filename
```

Note that our simple compiler *does NOT detect which platform you are running*. Thus, you can only run this code on **x86-64 platform**.



## Functions

This compiler support only no more than two extra parameters for function `printf()` such like

```c
printf("%d %d\n", 10 * 2, 4 * b);
```

We support `int`, `String`, `boolean` type in one argument, but only support `int` in two arguments.



## Limits

**You have to write `return 0;` by yourself in the main function to generate `ret i32 0`.**

You can't initial or assign a bool into int. e.g. `int a = 2 > 1;` or `int a; a = 2 > 1;`

No type casting.

We support \+, \-, \*, /, <<, >>, <, >, <=, >=, ==, !=. but not include &, |, ^, &&,  ||.



## Bonus

We support nested if-else statement.



## Standard of the CFG

The context-free grammar of this project is cited from the reference below

https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

https://gist.github.com/codebrainz/2933703



## No Preprocessor is Included

Thus, the declaration such as `#define`, `#include`, `#line`, `#undef`, `#error`, `#pragma`, `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif`, etc, is not declared in this project.

The types defined in another files or libraries, `uint8_t`, for example, can not be parsed correctly in this project.

