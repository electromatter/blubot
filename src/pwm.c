#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "pwm.h"
#include "crc16.h"

volatile char* volatile ptr[2];
volatile int off;
volatile char enable;
volatile char buf[14*2];

void pwm_init(void)
{
	/*ENABLE UART TX WITH INTERRUPT*/
	UCSR0B |= 0x48;
	/*8bit charaters*/
	UCSR0C |= 0x06;
	off = 0;
	ptr[0] = 0;
	ptr[1] = 0;
	enable = 0;
}

void pwm_enable(int en)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		enable = en;
	}
}

void pwm_timer(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(off == 0)
			return;
		if(off >= 14) {
			off = 0;
			if(enable)
				UDR0 = ptr[0][off++];
		} else {
			ptr[1] = ptr[0];
		}
	}
}

void pwm_set(char *val)
{
	volatile char *p = 0;
	uint16_t crc;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if(ptr[1] && ptr[1] != ptr[0])
			p = ptr[1];
		else
			if(ptr[0] == buf)
				p = buf + 14;
			else
				p = buf;
		
		p[0]  = (char)0xFF;
		p[1]  = 0x00;
		p[2]  = val[0];
		p[3]  = val[1];
		p[4]  = val[2];
		p[5]  = val[3];
		p[6]  = val[4];
		p[7]  = val[5];
		p[8]  = val[6];
		p[9]  = val[7];
		p[10] = val[8];
		p[11] = val[9];
		
		crc = crc16(p, 11);
		
		p[12] = (crc >> 8) & 0xFF;
		
		p[13] = crc & 0xFF;
		
		if(ptr[0] && off < 14) {
			ptr[1] = p;
		} else {
			ptr[0] = p;
			off = 0;
			if(enable)
				UDR0 = ptr[0][off++];
		}
/*
 * SENT VIA SERIAL PIN 3 (PD1/TXD) 115200 BAUD
 * ROBOTOPEN SHIELD PROTOCOL
 * [0] = 0xFF
 * [1] = 0x00
 * [2-11] = PWMx (0x7F is stopped), 
 * [12-13] = crc16 Big-Endian
 * MUST BE SENT EVERY 250ms
 * CRC16 Polynomial = 0xA001
 * PWMCRC = crc16(0, data);
 * SOLENOIDCRC = crc16(0, data) + 1;
 */
	}
}

ISR(USART_TX_vect)
{
	if(off >= 14) {
		if(!enable)
			ptr[0] = ptr[1] = 0;
		if(ptr[1]) {
			ptr[0] = ptr[1];
			ptr[1] = 0;
			off = -1;
		} else {
			return;
		}
	}
	UDR0 = ptr[0][off++];
}
