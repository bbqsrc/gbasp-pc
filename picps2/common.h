#ifndef __COMMON_H__
#define __COMMON_H__

volatile uint8_t kbd_start;
volatile uint8_t host_start;

/* Scancode enum */
#define ENTER  0
#define BKSP   1
#define A      2
#define B      3
#define L      4
#define R      5
#define UP     6
#define DOWN   7
#define LEFT   8
#define RIGHT  9
#define KBDBRK 10
#define PREFIX 11

#define DNW    6 // Do not want value, don't check for enabled
/* End enum */

const uint8_t sc[12] = {0x5a, 0x66, 0x1c, 0x32, 0x4b, 0x2d, 0x75, 0x72, 0x6b, 0x74, 0xf0, 0xe0}; 
volatile uint8_t en[DNW];

#endif

