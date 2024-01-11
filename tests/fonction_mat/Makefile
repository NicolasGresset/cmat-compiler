CFLAGS=-Wall -Wextra -Werror

all: exec exemple1 exemple2 exemple3

exec:
	gcc main.c ../../src/matrix.c -o exec $(CFLAGS)

exemple1:
	gcc main.c ../../src/matrix.c -DC_EXEMPLE_1 -o exemple1 $(CFLAGS)

exemple2:
	gcc main.c ../../src/matrix.c -DC_EXEMPLE_2 -o exemple2 $(CFLAGS)

exemple3:
	gcc main.c ../../src/matrix.c -DC_EXEMPLE_3 -o exemple3 $(CFLAGS)

clean:
	rm -f exec exemple1 exemple2 exemple3