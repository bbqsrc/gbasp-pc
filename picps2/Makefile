TARGET  := picps2
SRCS	:= picps2.c
OBJS	:= ${SRCS:.c=.o} 
PICC    := picc
PPATH   := /opt/picc-pro
MINGW   := i686-pc-mingw
CHIP    := 16f627a

PICFLAGS = -Q -DPICTEST 
CCFLAGS = -std=gnu99 -DTEST

.PHONY: all clean distclean test  
all:: pic test test-mingw

pic:: ${SRCS} Makefile
	${PICC} -I${PPATH}/include ${PICFLAGS} --chip=${CHIP} $< 

test-mingw:: ${SRCS} Makefile
	${MINGW}-gcc -o ${TARGET}.exe $<

test:: ${SRCS} Makefile
	${CC} ${CCFLAGS} -o ${TARGET} $<

clean:: 
	-rm -f *~ *.o ${TARGET} 

distclean:: clean
