To generate make files use cmake:
 * cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-avr-gcc.cmake

Then compile with make:
 * make

To build the generated elf into an intel hex file use avr-objcopy:
 * avr-objcpy -Oihex [src file] [dest file]

To flash the generated hex file with avrdude:
 * avrdude -p ATmega328P -b 115200 -c arduino -P [port] -U flash:w:[src hex file]

To program the generated EEPROM with avrdude use:
 * avrdude -p ATmega328P -b 115200 -c arduino -P [port] -U eeprom:w:[eeprom hex file]

Network Protocol:
 
 Timeout is 250ms
 
 Blubot broadcasts state information every 10ms:
 
 to 255.255.255.255:[port]
 
  id:4
 
  DATAPAYLOAD:arbitrary
 
 A Controler may enable Blubot by sending a state update atleast every 250ms:
 
   id:4
  
   enabled:1
  
   CONTROLPAYLOAD:arbitrary
 
 Because the protocol is inherently insecure, Blubot should only be operated on
 a secured network.
