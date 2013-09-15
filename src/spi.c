#include <avr/interrupt.h>

void spi_init(void)
{
	/*Set SS to HIGH OUTPUT*/
	PORTB |= 0x04;
	DDRB |= 0x04;
	
	/*
	 * WARNING: if the SS pin ever becomes a LOW INPUT then SPI
	 * automatically switches to Slave, so the data direction of
	 * the SS pin MUST be kept as OUTPUT.
	 */
	SPCR |= _BV(MSTR);
	SPCR |= _BV(SPE);

	/*Set SCK and MOSI as OUTPUT*/
	DDRB |= 0x28;
	DDRB &= ~0x10;
}

void spi_end(void)
{
	SPCR &= ~_BV(SPE);
}

void spi_setendian(uint8_t lsb)
{
	if(lsb) {
		SPCR |= _BV(DORD);
	} else {
		SPCR &= ~(_BV(DORD));
	}
}

void spi_datamode(uint8_t mode)
{
	SPCR = (SPCR & ~0x0C) | (mode & 0x0C);
}

void spi_clockdivider(uint8_t rate)
{
	SPCR = (SPCR & 0xFC) | (rate & 0x03);
	SPSR = (SPSR & 0xFE) | ((rate >> 2) & 0x01);
}

char spi_transfer(char data) {
	SPDR = data;
	while (!(SPSR & _BV(SPIF)));
	return SPDR;
}
