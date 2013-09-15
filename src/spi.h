#ifndef SPI_H
#define SPI_H

#include <inttypes.h>

void spi_init(void);
void spi_end(void);
void spi_setendian(uint8_t lsb);
void spi_datamode(uint8_t mode);
void spi_clockdivider(uint8_t rate);
char spi_transfer(char data);

#endif
