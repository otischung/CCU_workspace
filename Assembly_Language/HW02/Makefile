CC=arm-none-eabi-gcc
CFLAGS=-g -O0 --specs=nosys.specs

all: hw02.exe

hw02.exe: ./hw02.s
	${CC} ${CFLAGS} hw02.s -o hw02.exe

clean: 
	rm hw02.exe
