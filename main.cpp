/*
 * MAC ADDRESS Hard coded?
 * IP ADDRESS Hard coded?
 * upload protocol=arduino
 * upload speed=115200
 * SENT VIA SERIAL PIN 3 (PD1/TXD) 115200 BAUD
 * ROBOTOPEN SHIELD PROTOCOL
 * [0] = 0xFF
 * [1] = 0x00
 * [2-11] = PWMx (0x7F is stopped), 
 * [12-13] = crc16 Big-Endian
 * MUST BE SENT EVERY 250ms
 * CRC16 Polynomial = 0xA001
 * PWMCRC = crc16(0, data);
 * SOLENOIDCRC = crc16(0, data);
 * 
 * REIMPLIMENT IN C
 * 
 * OR HACK-ISH C++?
 */
//#include "libraries/SPI/SPI.h"

extern "C" {

#include "crc16.h"

}

int main(void)
{
	unsigned short t = crc16("test", 4);
	
	//REQUIRED LIBRARIES:
	//(SCHED PRIORITY)
	//DIO - ENCODERS (HIGH PRIORITY)
	//SPI - ETHERNET (MID PRIORITY)
	//HARDWARE SERIAL - PWM (MID PRIORITY)
	//EEPROM - CONFIG (LOW PRIORITY)
	//2WIRE - ACCELOROMETER (LOW PRIORITY)
	
	//PID:
	//TODO
	
	//Hardware Serial
	//Two buffers of 28 bytes
	//Takes aprox. 2.7ms to send the buffer
	//interupt on send ready
	
	//DIO POLL OR INTERUPT?
	
	//ETHERNET/SPI:
	//WILL BE MOST COMPLEX
	//Registers -
	
	//EEPROM: code ip, gateway ip, subnet mask and mac address
	//return eeprom_read_byte((unsigned char *) address);
	//eeprom_write_byte((unsigned char *) address, value);
}
