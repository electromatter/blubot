#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "crc16.h"
#include "enc.h"
#include "twi.h"
#include "spi.h"
#include "ip.h"
#include "pwm.h"
#include "config.h"

int main(void)
{
	char packet[1500];
	struct cfg_s cfg;
	
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
	eeprom_read_block(&eecfg,  &cfg, sizeof(struct cfg_s));
	
	ip_setipmac((char*)cfg.ip, (char*)cfg.subnet, (char*)cfg.mac);
	
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
		 *  ANALOG:
		 *   GYRO
		 *   TEMP
		 *  ACCELEROMETER
		 *  CONTROL STATION
		 *  PID?
		 */
		/*LOOP*/
	}
}
