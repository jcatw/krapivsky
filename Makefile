all: krapivsky

krapivsky: bstreap.o krapivsky.o
	${CC} ${CFLAGS} -Isrc/C -o krapivsky bstreap.o krapivsky.o

bstreap.o: src/C/bstreap.c
	${CC} ${CFLAGS} -Isrc/C -c src/C/bstreap.c

krapivsky.o: bstreap.o src/C/krapivsky.c
	${CC} ${CFLAGS} -Isrc/C -c src/C/krapivsky.c

clean:
	rm *.o krapivsky
