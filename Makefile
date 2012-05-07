################################
# Mon Mar 26 14:49:42 CST 2012 #
################################

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
MOVE          = mv -u

####### Output file and directory #######

OBJS_DIR    = Release

LIBRARY_DIR = Library

OBJS        = Game.o

NEED_UPDATE = Grid.o

TOTAL_LIBRARY = Player.o \
		Game.o \
		Display.o
	
TARGET      = Debug.exe

####### Compile #######

.c.o:
	${CC} -c ${CFLAGS} ${INCPATH} ${DEFINES} $< -o $@

.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCPATH} ${DEFINES} $< -o $@

####### Build rules #######

default: new_dir ${TARGET} move run

new_dir: 
	${MKDIR} ${OBJS_DIR}

${TARGET}: get_obj
	${LINK} -o $@ ${OBJS} ${LIBS} ${LIBRARY_MMIC} ${LIBRARY_GA}

get_obj: ${OBJS}

move:
	${MOVE} ${OBJS} ${TARGET} ${OBJS_DIR}

run: 
	./${OBJS_DIR}/${TARGET}

clean: 
	${DEL_FILE} ${OBJS_DIR}/${OBJS}

clean_all: clean
	${DEL_DIR} ${OBJS_DIR}

####### Update library #######

updateAll: reCompileAll moveAllToLibary

reCompileAll: ${TOTAL_LIBRARY}

moveAllToLibary: 
	${MOVE} ${TOTAL_LIBRARY} ${LIBRARY_DIR}

update: reCompile moveToLibary

reCompile: ${NEED_UPDATE}

moveToLibary: 
	${MOVE} ${NEED_UPDATE} ${LIBRARY_DIR}
