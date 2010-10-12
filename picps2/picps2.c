#include "picps2.h"

// CLK - clock pin (RA7)
// DATA - data pin (RA0)
// OPCODE - opcode pin (RA1)
// RB0-1 - Up,Dn,Lt,Rt
// RB2-7 - A,B,L,R,Start,Select

void clk_wait()
{
#ifdef TEST
	usleep(33);
#else
	while(!CLK){}; // loop until high
	while(CLK){};  // loop until low
#endif
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
void send(uint8_t sc) // INTERRUPT: ignited when one of the inputs is true
{
	// Clear some vars
	kbd_start = 1;
	//parityc = 0;
#ifdef TEST
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
		//if(DATA) // increment parityc if DATA is 1
		//	parityc++;
#ifdef TEST
		printf("%d", DATA);
#endif
		
	}
	// Odd parity bit
	clk_wait();
	//DATA = parityt[parityc];
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
	return 0;
}
