CXXSRCDIR=src/cc
CXXINCLUDE=-I${CXXSRCDIR}
CXXOBJDIR=build/objects/cc
CXXOPTS=-std=c++11 -arch x86_64 -lstdc++ -Lbuild/objects/cc -g
#CXX=gcc

CXXCOMPILE=${CXX} ${CPPFLAGS} ${CXXOPTS} ${CXXINCLUDE}


vpath %.o build/objects/cc
vpath %.cc src/cc
vpath %.hh src/cc


#C++
#all: krapivsky

all: krapivsky

krapivsky: krapivsky.o krapivskymodel.o degreenode.o common.o
	${CXXCOMPILE} -o build/krapivsky ${CXXOBJDIR}/krapivsky.o ${CXXOBJDIR}/krapivskymodel.o ${CXXOBJDIR}/degreenode.o ${CXXOBJDIR}/common.o

common.o: common.cc common.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/common.o -c ${CXXSRCDIR}/common.cc

#bignet.o: degreenode.o bstreap.o network.o krapivskymodel.o krapivsky.o
#	${CXXCOMPILE} -lstdc++ -o ${CXXOBJDIR}/bignet.o ${CXXOBJDIR}/krapivsky.o ${CXXOBJDIR}/krapivskymodel.o ${CXXOBJDIR}/network.o ${CXXOBJDIR}/bstreap.o ${CXXOBJDIR}/degreenode.o 

krapivsky.o: krapivskymain.cc 
	${CXXCOMPILE} -o ${CXXOBJDIR}/krapivsky.o -c ${CXXSRCDIR}/krapivskymain.cc

#bignet: krapivskymain.cc bstreap.o bstreapitem.o common.o \
#	degreenode.o directeddegreenetwork.o heapnode.o \
#	indegreebstreapitem.o krapivskymodel.o network.o \
#	node.o nodepair.o outdegreebstreapitem.o simulation.o
#	${CXXCOMPILE} -o build/bignet -c ${CXXSRCDIR}/krapivskymain.cc ${CXXOBJDIR}/*.o

#bstreap.o: bstreap.cc bstreap.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/bstreap.o -c ${CXXSRCDIR}/bstreap.cc

#bstreapitem.o: bstreapitem.cc bstreapitem.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/bstreapitem.o -c ${CXXSRCDIR}/bstreapitem.cc
#
#common.o: common.cc common.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/common.o -c ${CXXSRCDIR}/common.cc
#
degreenode.o: degreenode.cc degreenode.hh indegreenode.hh outdegreenode.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/degreenode.o -c ${CXXSRCDIR}/degreenode.cc 
#
#directeddegreenetwork.o: directeddegreenetwork.cc directeddegreenetwork.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/directeddegreenetwork.o -c ${CXXSRCDIR}/directeddegreenetwork.cc
#
#heapnode.o: heapnode.cc heapnode.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/heapnode.o -c ${CXXSRCDIR}/heapnode.cc
#
#indegreebstreapitem.o: indegreebstreapitem.cc indegreebstreapitem.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/indegreebstreapitem.o -c ${CXXSRCDIR}/indegreebstreapitem.cc
#
##model.o: model.hh
##	${CXXCOMPILE} -o ${CXXOBJDIR}/model.o -c ${CXXSRCDIR}/model.hh
#
krapivskymodel.o: krapivskymodel.cc krapivskymodel.hh
	${CXXCOMPILE} -o ${CXXOBJDIR}/krapivskymodel.o -c ${CXXSRCDIR}/krapivskymodel.cc
#
#network.o: network.cc network.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/network.o -c ${CXXSRCDIR}/network.cc
#
#node.o: node.cc node.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/node.o -c ${CXXSRCDIR}/node.cc
#
##nodelist.o: nodelist.hh
##	${CXXCOMPILE} -o ${CXXOBJDIR}/nodelist.o -c ${CXXSRCDIR}/nodelist.hh
#
#nodepair.o: nodepair.cc nodepair.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/nodepair.o -c ${CXXSRCDIR}/nodepair.cc
#
##nodeset.o: nodeset.hh
##	${CXXCOMPILE} -o ${CXXOBJDIR}/nodeset.o -c ${CXXSRCDIR}/nodeset.hh
##
#
#outdegreebstreapitem.o: outdegreebstreapitem.cc outdegreebstreapitem.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/outdegreebstreapitem.o -c ${CXXSRCDIR}/outdegreebstreapitem.cc
#
#setitem.o: setitem.cc setitem.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/setitem.o -c ${CXXSRCDIR}/setitem.cc
#
#simulation.o: simulation.cc simulation.hh
#	${CXXCOMPILE} -o ${CXXOBJDIR}/simulation.o -c ${CXXSRCDIR}/simulation.cc



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

ckrapivsky: cbstreap.o ckrapivsky.o cziggurat.o
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ckrapivsky ${COBJDIR}/*.o

cbstreap.o: src/C/bstreap.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/cbstreap.o -c ${CSRCDIR}/bstreap.c

ckrapivsky.o: ziggurat.o bstreap.o krapivsky.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/ckrapivsky.o -c ${CSRCDIR}/krapivsky.c

cziggurat.o: ziggurat.c
	${CC} ${CFLAGS} ${INCLUDE} ${COPTS} -o ${COBJDIR}/cziggurat.o -c lib/ziggurat.c

# general
clean:
	rm -f ${CXXOBJDIR}/*.o
	rm -f ${COBJDIR}/*.o
