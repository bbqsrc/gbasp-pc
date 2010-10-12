TARGET  := picps2
SRCS	:= picps2.c
OBJS	:= ${SRCS:.c=.o} 
PICC    := picc
PPATH   := /opt/picc-pro
MINGW   := i686-pc-mingw32
CHIP    := 16f627a

PICFLAGS = -Q -DPICTEST 
CCFLAGS = -std=gnu99 -DTEST

.PHONY: all clean distclean test  
all:: pic test test-mingw

release::
	${PICC} -I${PPATH}/include --chip=${CHIP} ${SRCS}

pic::
	${PICC} -I${PPATH}/include ${PICFLAGS} --chip=${CHIP} ${SRCS} 

pic-debug::
	${PICC} -S -I${PPATH}/include ${PICFLAGS} --chip=${CHIP} ${SRCS} 

test-mingw:: 
	${MINGW}-gcc -o ${TARGET}.exe ${SRCS}

test:: 
	${CC} ${CCFLAGS} -o ${TARGET} ${SRCS}

clean:: 
	-rm -f *~ *.o ${TARGET} funclist *.as *.cof *.hex *.hxl *.lst *.p1 *.pre *.sdb *.sym *.lst *.obj *.rlf

distclean:: clean
