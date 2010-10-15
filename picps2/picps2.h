#ifndef __PICPS2_H__
#define __PICPS2_H__
#define PIC
#include <htc.h>

// stdint to pic type
typedef unsigned char  uint8_t;
typedef signed char    int8_t;
typedef unsigned int   uint16_t;
typedef signed int     int16_t;
typedef signed long    int32_t;

#define usleep(x)\
asm("\tMOVLW "___mkstr(x>>2));\
asm("\tADDLW 0xFF");\
asm("\tBTFSS _STATUS, 2");\
asm("\tGOTO $ - 2");

void msleep(uint8_t cnt)
{
        uint8_t i;
        do {
                i = 4;
                do {
                        usleep(250);
                        CLRWDT();
                } while(--i);
        } while(--cnt);
}


#endif
