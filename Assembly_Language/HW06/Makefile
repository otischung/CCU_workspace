COMPILE=arm-none-eabi-gcc
OPTION=-g --specs=nosys.specs
OBJ=$(wildcard *.s)
TAR=$(patsubst %.s,%.exe,$(OBJ))

all: hw6.exe

hw6.exe: ./hw6_test.s ./numsort.s
	$(COMPILE) $(OPTION) hw6_test.s numsort.s -o hw6.exe

run: hw6.exe
	arm-none-eabi-gdb ./hw6.exe

test.s: ./test.c
	$(COMPILE) -mapcs-frame -S test.c

test: test.s
	$(COMPILE) $(OPTION) test.s -o test

run_test: test
	arm-none-eabi-gdb ./test

clean:
	rm -rf hw6.exe test.s test result.txt
