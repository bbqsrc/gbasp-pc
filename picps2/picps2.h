#ifndef __PICPS2_H__
#define __PICPS2_H__
#include <htc.h>

// WORKAROUND: stdint to pic type
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

#define OPCODE RA1
#define DATA RA0
#define CLK RA7

#endif
