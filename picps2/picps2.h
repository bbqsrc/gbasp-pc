#ifdef TEST
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#warning Test mode on, make sure you change some vars to test!

uint8_t OPCODE = 1;
uint8_t DATA = 1;
uint8_t CLK = 0;

uint8_t RB0 = 1;
uint8_t RB1 = 1;
uint8_t RB2 = 1;
uint8_t RB3 = 1;
uint8_t RB4 = 1;
uint8_t RB5 = 1;
uint8_t RB6 = 1;
uint8_t RB7 = 1;
#else
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
#endif /* TEST */

volatile uint8_t kbd_start;
volatile uint8_t host_start;
uint8_t hasht[11];

/* Scancodes */
#define BREAK (uint8_t) 0xF0
#define PREFIX (uint8_t) 0xE0
#define UP (uint8_t) 0x75
#define DOWN (uint8_t) 0x72
#define LEFT (uint8_t) 0x6B
#define RIGHT (uint8_t) 0x74
#define ENTER (uint8_t) 0x5A
#define BKSP (uint8_t) 0x66
#define A (uint8_t) 0x1C
#define B (uint8_t) 0x32
#define L (uint8_t) 0x4B
#define R (uint8_t) 0x2D
/* End scancodes */

typedef struct {
	uint8_t name[7];
	uint8_t scancode;
	uint8_t enabled;
} Button;
