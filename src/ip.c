#include "spi.h"

#define MR	(0x0000)	/*MODE*/
#define GAR	(0x0001)	/*GATEWAY*/
#define SUBR	(0x0005)	/*SUBNET*/
#define SHAR	(0x0009)	/*SRC MAC*/
#define SIPR	(0x000F)	/*SRC IP*/
#define IR	(0x0015)	/*INTERRUPT*/
#define IMR	(0x0016)	/*INTERRUPT MASK*/
#define RTR	(0x0017)	/*TIMEOUT ADDR*/
#define RCR	(0x0019)	/*RETRY COUNT*/
#define RMSR	(0x001A)	/*RECV MEM SIZE*/
#define TMSR	(0x001B)	/*TRANS MEM SIZE*/
#define PATR	(0x001C)	/*AUTH TYPE ADDR*/
#define PTIMER	(0x0028)	/*PPP LCP REQ TIMER*/
#define PMAGIC	(0x0029)	/*PPP LCP MAGIC*/
#define UIPR	(0x002A)	/*UNREACHABLE IP (UDP MODE)*/
#define UPORT	(0x002E)	/*UNREACHABLE PORT (UDP MODE)*/

static void write8(uint16_t addr, uint8_t u8)
{
	spi_begin();
	spi_transfer((char)0xF0);
	spi_transfer((addr >> 8) & 0xFF);
	spi_transfer(addr & 0xFF);
	spi_transfer(u8);
	spi_end();
}

static void write16(uint16_t addr, uint16_t u16)
{
	write8(addr, (u16 >> 8) & 0xFF);
	write8(addr + 1, u16 & 0xFF);
}

static void writen(uint16_t addr, void* d, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		write8(addr + i, *((char*)d + i));
	}
}

void ip_init(void)
{
	spi_init();

	write8(MR, 0x80);
	write8(TMSR, 0x55);
	write8(RMSR, 0x55);
}

void ip_setipmac(char *ip, char *subnet, char *mac)
{
	writen(SHAR, mac, 6);
	writen(SIPR, ip, 4);
	writen(SUBR, subnet, 4);
}
