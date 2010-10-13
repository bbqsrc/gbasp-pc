#if defined(linux) || defined(__APPLE__)
#include "linuxps2.h"
#else
#include "picps2.h"
#endif

#include "common.h"

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
		case KBDBRK:
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

void send(uint8_t but) // ignited when one of the inputs is true
{
	// Clear some vars
	kbd_start = 1;

#ifdef TEST
	printf("%x 0x%x ", but, sc[but]);
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
		DATA = (sc[but] >> i) & 1;
#ifdef TEST
		printf("%d", DATA);
#endif
		
	}
	// Odd parity bit
	clk_wait();
	DATA = parity(but);

#ifdef TEST
	printf("|%d", DATA);
#endif

	clk_wait();
	DATA = 1; // Send end bit (1)
	CLK = 0xFF;

#ifdef TEST
	printf("|%d %s \n", DATA, nm[but]);
#endif

	kbd_start = 0;
	
	// THE END.
}

void dpad_chars()
{
	if(P_DPADE)
	{
		send(PREFIX);
		if(!P_DPAD0 && !P_DPAD1){
			send(UP);
			return;
		}
		if(!P_DPAD0 && P_DPAD1){
			send(RIGHT);
			return;
		}
		if(P_DPAD0 && !P_DPAD1){
			send(LEFT);
			return;
		}
		if(P_DPAD0 && P_DPAD1){
			send(DOWN);
			return;
		}
	}
	return;
}


void chk_pins()
{	
#ifdef TEST
	printf("\nSaved:%x, ", saved);
#endif
	delta = saved ^ ~P_INPUT;
	released = (delta & saved);// & 0x3F); // only first 6
	saved = ~P_INPUT; 
#ifdef TEST
	printf("Delta:%x, Rel:%x, NSaved:%x\n", delta, released, saved);
#endif
	if (released){
		if(released & 1<<A){
			send(KBDBRK);
			send(A);
		}
		if(released & 1<<B){
			send(KBDBRK);
			send(B);
		}
		if(released & 1<<L){
			send(KBDBRK);
			send(L);
		}
		if(released & 1<<R){
			send(KBDBRK);
			send(R);
		}
		if(released & 1<<ENTER){
			send(KBDBRK);
			send(ENTER);
		}
		if(released & 1<<BKSP){
			send(KBDBRK);
			send(BKSP);
		}		
	}
}


void ripple_chars()
{
	dpad_chars();
	if(!P_A)
		send(A);
	if(!P_B)
		send(B);
	if(!P_L)
		send(L);
	if(!P_R)
		send(R);
	if(!P_START)
		send(ENTER);
	if(!P_SELECT)
		send(BKSP);
	return;
}

void test()
{
#ifdef TEST
	printf("PICPS2 TEST RUN, LET'S GO!\n");
	printf("Parity 0: %d %d %d %d %d\n", PREFIX, UP, LEFT, A, B);
#endif
	chk_pins();
	ripple_chars();
	P_DPADE = 1;
	chk_pins();
	ripple_chars();
	P_INPUT += 1<<A;
	P_A = 1;
	chk_pins();
	ripple_chars();
	chk_pins();
	ripple_chars();
	chk_pins();
	ripple_chars();
	chk_pins();
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
	CLK_DIR = 0x00; // set CLK to output mode
	BUTS_DIR = 0xFF; // sets all PORTB to input mode
	CLK = 1; // Init on HIGH
#endif
	return 0;
}
