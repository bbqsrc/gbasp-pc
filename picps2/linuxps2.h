#ifndef __LINUXPS2_H__
#define __LINUXPS2_H__
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

const uint8_t nm[12][7] = {
"ENTER", "BKSP", "A", "B", "L", "R", 
"UP", "DOWN", "LEFT", "RIGHT", "KBDBRK", "PREFIX"
};

#endif 
