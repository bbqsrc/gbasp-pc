#include "picps2.h"

// CLK - clock pin (RA7)
// DATA - data pin (RA0)
// OPCODE - opcode pin (RA1)
// RB0-1 - Up,Dn,Lt,Rt
// RB2-7 - A,B,L,R,Start,Select
Button ecode = {"BREAK", BREAK};
Button prefix = {"PREFIX", PREFIX};
Button up = {"UP", UP};
Button down = {"DOWN", DOWN};
Button left = {"LEFT", LEFT};
Button right = {"RIGHT", RIGHT};
Button enter = {"ENTER", ENTER};
Button bksp = {"BKSP", BKSP};
Button a = {"A", A};
Button b = {"B", B};
Button l = {"L", L};
Button r = {"R", R};

void clk_set()
{
	usleep(16);
	CLK = 1;
	usleep(16);
	CLK = 0;
}

void clk_wait()
{
	clk_set(); // nice hack, probably not good
	return;
}

uint8_t parity(uint8_t p)
{
	switch(p){
		case PREFIX:
		case UP:
		case LEFT:
		case A:
		case B:
			return 0;
	}
	return 1;
}

void io_change_interrupt()
{
	return; //stub
}

void send(Button *but) // INTERRUPT: ignited when one of the inputs is true
{
	if(but->scancode != BREAK && but->enabled)
		send(&ecode);
		
	// Clear some vars
	kbd_start = 1;

#ifdef TEST
	printf("en:%d ", but->enabled);
	printf("0x%x ", but->scancode);
#endif

	clk_wait(); // If low, send data:
	DATA = 0;  // Send start bit (0) on clk

#ifdef TEST
	printf("%d|", DATA);
#endif

	// Send buffer of bits on clock until empty
	int i; // C99 lolwhut
	for (i = 0; i < 8; i++)
	{
		clk_wait(); // Check CLK is low
		DATA = (but->scancode >> i) & 1;
#ifdef TEST
		printf("%d", DATA);
#endif
		
	}
	// Odd parity bit
	clk_wait();
	DATA = parity(but->scancode);

#ifdef TEST
	printf("|%d", DATA);
#endif

	clk_wait();
	DATA = 1; // Send end bit (1)
	CLK = 0xFF;

#ifdef TEST
	printf("|%d %s \n", DATA, but->name);
#endif

	kbd_start = 0;
	
	if(but->scancode != BREAK){
		if(but->enabled)
			but->enabled = 0;
		else but->enabled = 1;
	}
	// THE END.
}

void dpad_chars()
{
	if(OPCODE)
	{
		send(&prefix);
		if(!RB0 && !RB1){
			send(&up);
			return;
		}
		if(!RB0 && RB1){
			send(&right);
			return;
		}
		if(RB0 && !RB1){
			send(&left);
			return;
		}
		if(RB0 && RB1){
			send(&down);
			return;
		}
	}
	return;
}

void ripple_chars()
{
	dpad_chars();
	if(RB2)
		send(&a);
	if(RB3)
		send(&b);
	if(RB4)
		send(&l);
	if(RB5)
		send(&r);
	if(RB6)
		send(&enter);
	if(RB7)
		send(&bksp);
	return;
}

void test()
{
#ifdef TEST
	printf("PICPS2 TEST RUN, LET'S GO!\n");
	printf("Parity 0: %d %d %d %d %d\n", PREFIX, UP, LEFT, A, B);
#endif
	int lol;
	for(lol = 0; lol < 8; lol++){
		ripple_chars();
	}
	return;
}

int main()
{
#ifdef TEST
	test();
#endif
#ifdef PICTEST
	test();
#endif
#ifndef TEST // protects from non-useful code
	// set PORTA to digital here!
	TRISA0 = 0; // sets CLK to output mode
	CLK = 1; // Init on HIGH
#endif
	return 0;
}
