CC?=gcc-11
CFLAGS=-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
CLIB=-lm

all: sinr sinr_random sinr_II

sinr: ./sinr.c
	${CC} ${CFLAGS} sinr.c -o sinr ${CLIB}

sinr_random: ./sinr_random.c
	${CC} ${CFLAGS} sinr_random.c -o sinr_random ${CLIB}

sinr_min: ./sinr_min.c
	${CC} ${CFLAGS} sinr_min.c -o sinr_min ${CLIB}

sinr_II: ./sinr_II.c
	${CC} ${CFLAGS} sinr_II.c -o sinr_II ${CLIB}

sinr_by_Sine_Wu: ./sinr_by_Sine_Wu.c
	${CC} ${CFLAGS} sinr_by_Sine_Wu.c -o sinr_by_Sine_Wu ${CLIB}

clean: 
	rm -f sinr sinr_random sinr_min sinr_II sinr_by_Sine_Wu
