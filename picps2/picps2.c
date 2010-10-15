#if defined(linux) || defined(__APPLE__)
#include "linuxps2.h"
#else
#include "picps2.h"
#endif

#include "common.h"

void clock_set()
{
	usleep(16);
	CLK = 0;
	usleep(16);
	CLK = 1;
}

void clock_wait()
{
	clock_set(); // nice hack, probably not good
	return;
}


#ifndef PIC
void
#else
interrupt
#endif
isr()
{
#ifdef PIC
	//TMR1IE
	// below is some stubs, do you enjoy stubs
	if(RBIF){
		RBIF = 0;
		return;
	}
	if(RBIE){
		RBIE = 0;
		return;
	}
	if(BKLT_I){
		// Timer check pl0x
		BKLT_O = ON;
	}
	else{
		BKLT_O = OFF;
	}
#endif
	return;
}

uint8_t parity(const uint8_t p)
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

void send(const uint8_t but) // ignited when one of the inputs is true
{
	CLK_MODE = OUTPUT; // output!
	kbd_start = 1;

#ifdef TEST
	printf("%x 0x%x ", but, sc[but]);
#endif

	clock_wait(); // If low, send data:
	DATA = 0;  // Send start bit (0) on clock

#ifdef TEST
	printf("%d|", DATA);
#endif

	// Send buffer of bits on clock until empty
	int i; // C99 lolwhut
	for (i = 0; i < 8; i++)
	{
		clock_wait(); // Check CLK is low
		DATA = (sc[but] >> i) & 1;
#ifdef TEST
		printf("%d", DATA);
#endif
		
	}
	// Odd parity bit
	clock_wait();
	DATA = parity(but);

#ifdef TEST
	printf("|%d", DATA);
#endif

	clock_wait();
	DATA = 1; // Send end bit (1)
	CLK = 0xFF;

#ifdef TEST
	printf("|%d %s \n", DATA, nm[but]);
#endif

	kbd_start = 0;
	CLK_MODE = INPUT;
	// THE END.
}

void check_button_release()
{	
#ifdef TEST
	printf("\nSaved:%x, ", saved);
#endif
	delta = saved ^ P_INPUT;
	released = (delta & saved & 0x3F); // only first 6
	saved = P_INPUT; 
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

void check_dpad()
{
	if(P_DPADE)
	{
		send(PREFIX);
		if(!P_DPAD1 && !P_DPAD0){
			send(UP);
			return;
		}
		if(!P_DPAD1 && P_DPAD0){
			send(RIGHT);
			return;
		}
		if(P_DPAD1 && !P_DPAD0){
			send(LEFT);
			return;
		}
		if(P_DPAD1 && P_DPAD0){
			send(DOWN);
			return;
		}
	}
	return;
}

void check_button_press()
{
	check_dpad();
	if(P_A)
		send(A);
	if(P_B)
		send(B);
	if(P_L)
		send(L);
	if(P_R)
		send(R);
	if(P_START)
		send(ENTER);
	if(P_SELECT)
		send(BKSP);
	return;
}

void test()
{
#ifdef TEST
	printf("PICPS2 TEST RUN, LET'S GO!\n");
	printf("Parity 0: %d %d %d %d %d\n", PREFIX, UP, LEFT, A, B);
	check_button_release();
	check_button_press();
	//P_DPADE = 1;
	check_button_release();
	check_button_press();
	P_INPUT += 1<<A;
	P_A = PRESS;
	check_button_release();
	check_button_press();
#endif
	return;
}

uint8_t main()
{
#ifdef TEST
	test();
#endif // protects from non-useful code
	// set PORTA to digital here!
	/* Init */
#ifdef PIC
	P_INPUT = 0;
	CTRL_INPUT = 0;
#endif
	CMCON = 0x07;      //Turn comparitors off
	P_MODES = 0xFF;    // sets all DPAD to input mode
	CTRL_MODES = 0x97; // sets control I/O
	CLK_MODE = INPUT;  // set CLK to input mode

	/* End Init */

	for(;;){
		check_button_release();
		check_button_press();
		msleep(SLPT);
	}
}
