COMPILE=arm-none-eabi-gcc
OPTION=-g --specs=nosys.specs
OBJ=$(wildcard *.s)
TAR=$(patsubst %.s,%.exe,$(OBJ))

# all: $(TAR)

# %.exe : %.s
# 	$(COMPILE) $(OPTION) $< -o $@

all: hw4.exe

hw4.exe: ./hw4_test.s ./numsort.s
	$(COMPILE) $(OPTION) hw4_test.s numsort.s -o hw4.exe

clean:
	rm -rf *.exe
