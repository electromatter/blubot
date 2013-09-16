#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "crc16.h"
#include "enc.h"
#include "twi.h"
#include "spi.h"
#include "ip.h"
#include "pwm.h"

int main(void)
{
	char packet[1500];
	char mac[6];
	char ip[4];
	char subnet[4];
	char port[2];
	char id[4];
	
	/*wait 500 for ethernet*/
	_delay_ms(500);
	
	enc_init();
	twi_init();
	spi_init();
	ip_init();
	pwm_init();
	sei();
	
	/*
	 * EEPROM:
	 * Mac Address:6
	 * IP:4
	 * Subnet Mask:4
	 * Port:2
	 * ID:4
	 */
	eeprom_read_block((void*)0,  mac, 6);
	eeprom_read_block((void*)6,  ip, 4);
	eeprom_read_block((void*)10, subnet, 4);
	eeprom_read_block((void*)14, port, 2);
	eeprom_read_block((void*)16, id, 4);
	
	ip_setipmac(ip, subnet, mac);
	
	while(1) {
		/*
		 * Provide encoder deltas
		 * Provide Integrated/Corrected Gyro
		 * Accelerometer?
		 * Pipe PWMS
		 * Pipe Spike
		 * IP? - TCP/UDP
		 * 
		 * Do reliability on cpu side.
		 * Send immediate acks only.
		 * 
		 * Timeout of 250 ms?
		 */
		/* TODO:
		 *  GYRO
		 *  TEMP
		 *  ACCELEROMETER
		 *  CONTROL STATION
		 */
		/*LOOP*/
	}
}
