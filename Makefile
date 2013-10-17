CXXSRCDIR=src/cc
INCLUDE=-I${CXXSRCDIR}
CXXOPTS=-std=c++11 -m64

CXXCOMPILE=${CXX} ${CPPFLAGS} ${CXXOPTS} ${INCLUDE}
CXXOBJDIR=build/objects/cc

vpath %.o build/objects/cc
vpath %.cc src/cc
vpath %.hh src/cc


#C++
all: bignet

bignet: network.o node.o nodepair.o simulation.o
	${CXXCOMPILE} -o build/bignet ${CXXOBJDIR}/*.o

#common.o: common.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/common.o -c ${CXXSRCDIR}/common.hh

#model.o: model.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/model.o -c ${CXXSRCDIR}/model.hh

network.o: network.cc network.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/network.o -c ${CXXSRCDIR}/network.cc

node.o: node.cc node.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/node.o -c ${CXXSRCDIR}/node.cc

#nodelist.o: nodelist.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/nodelist.o -c ${CXXSRCDIR}/nodelist.hh

nodepair.o: nodepair.cc nodepair.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/nodepair.o -c ${CXXSRCDIR}/nodepair.cc

#nodeset.o: nodeset.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/nodeset.o -c ${CXXSRCDIR}/nodeset.hh
#
simulation.o: simulation.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/simulation.o -c ${CXXSRCDIR}/simulation.cc



#C
CSRCDIR=src/C
INCLUDE = -Isrc/C -Ilib
COPTS=-lm -m64
COBJDIR=build/objects/c

vpath %.o build/objects/c
vpath %.c src/C
vpath %.h src/C
vpath ziggurat.% lib/

#all: krapivsky

krapivsky: bstreap.o krapivsky.o ziggurat.o
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o krapivsky ${COBJDIR}/*.o

bstreap.o: src/C/bstreap.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/bstreap.o -c ${CSRCDIR}/bstreap.c

krapivsky.o: ziggurat.o bstreap.o krapivsky.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/krapivsky.o -c ${CSRCDIR}/krapivsky.c

ziggurat.o: ziggurat.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/ziggurat.o -c lib/ziggurat.c

# general
clean:
	rm -f ${CXXOBJDIR}/*.o
	rm -f ${COBJDIR}/*.o
