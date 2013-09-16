#include "config.h"

/*MAC address: Should be unique*/
#define MAC	{0x02, 0x68, 0xb3, 0x29, 0xda, 0x98}
/*IP: 192.168.1.2 (default)*/
#define IP	{192, 168, 1, 2}
/*SUBNET: 255.255.255.0 (default)*/
#define SUBNET	{255, 255, 255, 0}
/*PORT: 6584 (default)*/
#define PORT 	(6584)
/*ID: 1 (default)*/
#define ID 	(1)

struct cfg_s EEMEM eecfg = {
	MAC,
	IP,
	SUBNET,
	{(uint8_t)((((uint16_t)PORT) >> 8) & 0xFF),
	 (uint8_t)(((uint16_t)PORT) & 0xFF)},
	ID,
};
