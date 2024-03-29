#ifndef CONFIG_H
#define CONFIG_H

#include <avr/eeprom.h>

struct cfg_s {
	uint8_t mac[6];
	uint8_t ip[4];
	uint8_t subnet[4];
	char port[2];
	int32_t id;
} __attribute__ ((__packed__));

extern struct cfg_s EEMEM eecfg;

#endif
