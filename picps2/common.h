#ifndef __COMMON_H__
#define __COMMON_H__

#define SLPT    25 // how many ms to delay
#define INPUT   1
#define OUTPUT  0
#define PRESS   1
#define RELEASE 0
#define ON      1
#define OFF     0

volatile uint8_t kbd_start;
volatile uint8_t host_start;
volatile uint8_t int_status;

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


#define DATA_MODE   TRISB0
#define CLK_MODE    TRISB7

#define CTRL_MODES  TRISB // 0b11010101
#define CTRL_INPUT  PORTB
#define DATA     RB0
#define USB_SEL  RB1 // ON = USB, OFF = USART via RS232 or whatever
#define P_DPADE  RB2
#define BKLT_O   RB3
#define BKLT_I   RB4
#define CLK      RB6
#define WAKEUP   RB7 //unused, interrupt for all buttons

#define P_MODES  TRISA
#define P_INPUT  PORTA
#define P_START  RA0
#define P_SELECT RA1
#define P_A      RA2
#define P_B      RA3
#define P_L      RA4
#define P_R      RA5
#define P_DPAD0  RA6
#define P_DPAD1  RA7

/*
<MrTrick> debouncing is important - simple way to do it: turn IOC on, when it's triggered turn IOC off, start a timer. (With TMRxIE set) When the timer overflows, disable TMRxIE and set IOC again, *then* check the button state.
*/

uint8_t saved = 0x00;
uint8_t delta = 0;
uint8_t released = 0;

#endif

