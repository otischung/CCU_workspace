COMPILE=arm-none-eabi-gcc
OPTION=-g --specs=nosys.specs
OBJ=$(wildcard *.s)
TAR=$(patsubst %.s,%.exe,$(OBJ))

all: hw5.exe

hw5.exe: ./hw5_test.s ./numsort.s
	$(COMPILE) $(OPTION) hw5_test.s numsort.s -o hw5.exe

run: hw5.exe
	arm-none-eabi-gdb ./hw5.exe

test.s: ./test.c
	$(COMPILE) -mapcs-frame -S test.c

test: test.s
	$(COMPILE) $(OPTION) test.s -o test

run_test: test
	arm-none-eabi-gdb ./test

clean:
	rm -rf hw5.exe test.s test
