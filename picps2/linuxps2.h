#ifndef __LINUXPS2_H__
#define __LINUXPS2_H__
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#warning Test mode on, make sure you change some vars to test!

uint8_t RA1 = 0;
uint8_t RA0 = 1;
uint8_t RA7 = 0;
uint8_t PORTB = 0x00;

int16_t RB0 = 0;
int16_t RB1 = 0;
int16_t RB2 = 0;
int16_t RB3 = 0;
int16_t RB4 = 0;
int16_t RB5 = 0;
int16_t RB6 = 0;
int16_t RB7 = 0;

const uint8_t nm[12][7] = {
"ENTER", "BKSP", "A", "B", "L", "R", 
"UP", "DOWN", "LEFT", "RIGHT", "KBDBRK", "PREFIX"
};

#endif 
