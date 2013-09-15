#include <util/delay.h>
#include <avr/interrupt.h>

#include "crc16.h"
#include "enc.h"
#include "twi.h"
#include "spi.h"
#include "ip.h"
#include "pwm.h"

int main(void)
{
	_delay_ms(500);
	enc_init();
	twi_init();
	spi_init();
	ip_init();
	pwm_init();
	sei();
	while(1) {
		/*LOOP*/
	}
}
