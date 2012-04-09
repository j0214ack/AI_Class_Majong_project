########################################
####### My Makefile format       #######
####### Sun Mar 11 20:30:27 201  #######
########################################


####### Compiler, linker, tools and options #######

CC            = /usr/bin/gcc
CXX           = /usr/bin/g++
LINK          = ${CXX}
DEFINES       = 
CFLAGS        = -O3 -Wall ${DEFINES}
CXXFLAGS      = -O3 -Wall ${DEFINES}
LIBS          = 
INCPATH       =
DEL_FILE      = rm -f
DEL_DIR       = rm -rf
MKDIR         = mkdir -p
MOVE          = mv

####### Output file and directory #######

OBJS_DIR      = Release

OBJS          = main.o 

TARGET      = Release.exe

####### Compile #######

.c.o:
	${CC} -c ${CFLAGS} ${INCPATH} $< -o $@

.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCPATH} $< -o $@

####### Build rules #######

default: new_dir ${TARGET} move run

new_dir: 
	${MKDIR} ${OBJS_DIR}

${TARGET}: get_obj
	${LINK} -o $@ ${OBJS} ${LIBS}

get_obj: ${OBJS}

move:
	${MOVE} ${OBJS} ${TARGET} ${OBJS_DIR}

run: 
	./${OBJS_DIR}/${TARGET}

clean: 
	${DEL_FILE} ${OBJS_DIR}/${OBJS}

clean_all: clean
	${DEL_DIR} ${OBJS_DIR}



