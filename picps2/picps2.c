#include "picps2.h"

// CLK - clock pin (RA7)
// DATA - data pin (RA0)
// OPCODE - opcode pin (RA1)
// RB0-1 - Up,Dn,Lt,Rt
// RB2-7 - A,B,L,R,Start,Select


uint8_t *ht(uint8_t x)
{
	switch(x){
		case UP:
			return &hasht[0];
		case DOWN:
			return &hasht[1];
		case LEFT:
			return &hasht[2];
		case RIGHT:
			return &hasht[3];
		case ENTER:
			return &hasht[4];
		case BKSP:
			return &hasht[5];
		case A:
			return &hasht[6];
		case B:
			return &hasht[7];
		case L:
			return &hasht[8];
		case R:
			return &hasht[9];
	}
	return &hasht[10];
}

void clk_set()
{
#ifdef TEST
	usleep(33);
#else
	DelayUs(16);
	CLK = 1;
	DelayUs(16);
	CLK = 0;
#endif
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
void send(uint8_t sc) // INTERRUPT: ignited when one of the inputs is true
{
	if(sc != BREAK && *ht(sc) == 1)
		send(BREAK);
		
	// Clear some vars
	kbd_start = 1;

#ifdef TEST
	printf("ht:%d\n", *ht(sc));
	printf("%d\n", sc);
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
		DATA = (sc >> i) & 1;
#ifdef TEST
		printf("%d", DATA);
#endif
		
	}
	// Odd parity bit
	clk_wait();
	DATA = parity(sc);

#ifdef TEST
	printf("|%d", DATA);
#endif

	clk_wait();
	DATA = 1; // Send end bit (1)

#ifdef TEST
	printf("|%d\n", DATA);
#endif

	kbd_start = 0;
	
	if(sc != BREAK){
		if(*ht(sc) == 1)
			*ht(sc) = 0;
		else *ht(sc) = 1;
	}
	// THE END.
}

void dpad_chars()
{
	if(OPCODE)
	{
		send(PREFIX);
		if(!RB0 && !RB1){
			send(UP);
			return;
		}
		if(!RB0 && RB1){
			send(RIGHT);
			return;
		}
		if(RB0 && !RB1){
			send(LEFT);
			return;
		}
		if(RB0 && RB1){
			send(DOWN);
			return;
		}
	}
	return;
}

void ripple_chars()
{
	dpad_chars(); // works around lack of else if
	if(RB2)
		send(A);
	if(RB3)
		send(B);
	if(RB4)
		send(L);
	if(RB5)
		send(R);
	if(RB6)
		send(ENTER);
	if(RB7)
		send(BKSP);
	return;
}

void test()
{
#ifdef TEST
	printf("PICPS2 TEST RUN, LET'S GO!\n");
	printf("Parity 0: %d %d %d %d %d\n", PREFIX, UP, LEFT, A, B);
#endif
	ripple_chars();
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

#endif
	return 0;
}
