CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
CFLAGS=--specs=rdimon.specs -lgcc -lc -lm -lrdimon

all: hw1.o hw1.exe sample_O0.o sample_O3.o

hw1.o: ./hw1.s
	${AS} hw1.s -o hw1.o

hw1.exe: ./hw1.s
	${CC} ${CFLAGS} hw1.s -o hw1.exe

sample_O0.o: ./sample.c
	${CC} ${CFLAGS} -O0 -S sample.c -o sample_O0.s
	${AS} sample_O0.s -o sample_O0.o

sample_O3.o: ./sample.c
	${CC} ${CFLAGS} -O3 -S sample.c -o sample_O3.s
	${AS} sample_O3.s -o sample_O3.o

clean: 
	rm hw1.o hw1.exe sample_O0.o sample_O3.o sample_O0.s sample_O3.s

# https://stackoverflow.com/questions/23102500/compiling-using-arm-none-eabi-gcc-and-linking-library-liba-a-error
