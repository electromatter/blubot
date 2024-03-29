#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>
#include <inttypes.h>

uint16_t crc16(const volatile char *buf, size_t len);

#endif
