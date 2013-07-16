INCLUDE = -Isrc/C -Ilib

all: krapivsky

krapivsky: bstreap.o krapivsky.o ziggurat.o
	${CC} ${CFLAGS} ${INCLUDE} -o krapivsky bstreap.o krapivsky.o ziggurat.o

bstreap.o: src/C/bstreap.c
	${CC} ${CFLAGS} ${INCLUDE} -c src/C/bstreap.c

krapivsky.o: ziggurat.o bstreap.o src/C/krapivsky.c
	${CC} ${CFLAGS} ${INCLUDE} -c src/C/krapivsky.c

ziggurat.o: lib/ziggurat.c
	${CC} ${CFLAGS} ${INCLUDE} -c lib/ziggurat.c

clean:
	rm *.o krapivsky
