# Compiler Design Project 1: Lexical Analyzer

## Author Information

CCU CSIE 3B

408410120

鍾博丞

## Environment

ANTLR 4.9.3 is used in this project. Makefile will download `antlr-4.9.3-complete.jar` using `wget` automatically if it doesn't exist in the project directory.

The syntax of ANTLR4 is more like regular expression than ANTLR3. For example, both `[a-zA-Z]` and `'a' .. 'z' | 'A' .. 'Z` are supported in ANTLR4, whereas ANTLR3 supports only the latter.

## Makefile / Execution

`make run c_sorce_filename` is same as `java -cp ./antlr-4.9.3-complete.jar:. testLexer c_sorce_filename]`

## Comment Match Method

We use `‹.*?›` to match anything between the two delimiters of the comment. The option “dot matches line breaks” that most regex engines have allows this to span multiple lines. We need to use a lazy quantifier to make sure that the comment stops at the first `*/` after the `/*`, rather than at the last `*/` in the file.

Reference: https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch07s06.html

