#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

volatile char last[4];
volatile int delta[4];

/* 4X encoder count
 * Map encoder values to count delta
 * count += enctab[(last[x] << 2) | current];
 * .0 is the unhandled error case, in which the encoder signals to fast, or
 * the encoder is stuck, however the interrupt should service the encoder
 * fast enough for this not to be an issue
 */
PROGMEM const char enctab[] = {
	0,-1, 1,.0,
	1, 0,.0,-1,
       -1,.0, 0, 1,
       .0, 1,-1, 0,
};

void enc_init(void)
{
	PORTB &= ~0x03;
	DDRB &= ~0x03;
	PORTD &= ~0xFC;
	DDRD &= ~0xFC;
	
	PCMSK0 |= 0x03;
	PCMSK2 |= 0xFC;
	
	PCICR  |= 0x05;
	
	last[0] = 0;
	last[1] = 0;
	last[2] = 0;
	last[3] = 0;
	
	delta[0] = 0;
	delta[1] = 0;
	delta[2] = 0;
	delta[3] = 0;
}

void enc_delta(int *d) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		d[0] = delta[0];
		d[1] = delta[1];
		d[2] = delta[2];
		d[3] = delta[3];
	}
}

void enc_reset(void) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		delta[0] = 0;
		delta[1] = 0;
		delta[2] = 0;
		delta[3] = 0;
	}
}

static void pinchange(void)
{
	/*Atomicly read pind pinb*/
	char t = ((PIND << 6) & 0xC0) | ((PINB >> 2) & 0x3F);
	
	last[0] = ((t >> 6) & 0x03) | (last[0] << 2);
	last[1] = ((t >> 4) & 0x03) | (last[1] << 2);
	last[2] = ((t >> 2) & 0x03) | (last[2] << 2);
	last[3] = ((t >> 0) & 0x03) | (last[3] << 2);
	
	delta[0] += (char)pgm_read_byte_near(enctab + last[0]);
	delta[1] += (char)pgm_read_byte_near(enctab + last[1]);
	delta[2] += (char)pgm_read_byte_near(enctab + last[2]);
	delta[3] += (char)pgm_read_byte_near(enctab + last[3]);
	
	last[0] &= 0x03;
	last[1] &= 0x03;
	last[2] &= 0x03;
	last[3] &= 0x03;
}

ISR(PCINT0_vect)
{
	pinchange();
}

ISR(PCINT2_vect)
{
	pinchange();
}
/*
 * PCI2 = PCINT[23:16]
 * PCI0 = PCINT[7:0]
 * PB0 - 8 - PCINT00 - B4
 * PB1 - 7 - PCINT01 - A4
 * PD2 - 6 - PCINT18 - B3
 * PD3 - 5 - PCINT19 - A3
 * PD4 - 4 - PCINT20 - B2
 * PD5 - 3 - PCINT21 - A2
 * PD6 - 2 - PCINT22 - B1
 * PD7 - 1 - PCINT23 - A1
 */
