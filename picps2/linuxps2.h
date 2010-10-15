#ifndef __LINUXPS2_H__
#define __LINUXPS2_H__
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#warning Test mode on, make sure you change some vars to test!

#define msleep(x)\
usleep(x * 1000);

uint8_t CLK_MODE = 0;
uint8_t BUT_MODES = 0;

uint8_t RBIF = 0;
uint8_t PORTA = 0x00;
int16_t RA0 = 1;
int16_t RA1 = 0;
int16_t RA2 = 0;
int16_t RA3 = 1;
int16_t RA4 = 0;
int16_t RA5 = 0;
int16_t RA6 = 0;
int16_t RA7 = 0;

uint8_t PORTB = 0x00;
int16_t RB0 = 1;
int16_t RB1 = 0;
int16_t RB2 = 0;
int16_t RB3 = 1;
int16_t RB4 = 0;
int16_t RB5 = 0;
int16_t RB6 = 0;
int16_t RB7 = 0;

uint8_t TRISB = 0;
uint8_t TRISB7 = 0;
uint8_t TRISA = 0;
uint8_t CMCON = 0;

const uint8_t nm[12][7] = {
"ENTER", "BKSP", "A", "B", "L", "R", 
"UP", "DOWN", "LEFT", "RIGHT", "KBDBRK", "PREFIX"
};

#endif 
