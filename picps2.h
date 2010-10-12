#ifdef TEST
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#warning Test mode on, make sure you change some vars to test!

uint8_t OPCODE = 1;
uint8_t DATA = 1;
uint8_t CLK = 0;

uint8_t RB0 = 0;
uint8_t RB1 = 1;
uint8_t RB2 = 0;
uint8_t RB3 = 1;
uint8_t RB4 = 0;
uint8_t RB5 = 1;
uint8_t RB6 = 1;
uint8_t RB7 = 0;
#else
#include <htc.h>

// WORKAROUND FOR LACK OF uint8_t
#define uint8_t char

#define OPCODE RA1
#define DATA RA0
#define CLK RA7
#endif /* TEST */

//uint8_t parityc;
uint8_t kbd_start;
uint8_t host_start;

/* Scancodes */
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

/*
const uint8_t parityt[] = 
{
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
};*/

