To generate make files use cmake:
 * cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-avr-gcc.cmake

Then compile with make:
 * make

To generate FLASH image from elf:
 * avr-objcpy -Oihex -R .eeprom [src file] [dest file]

To generate EEPROM image from elf:
 * avr-objcpy -Oihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings [src file] [dest file]

To flash the generated hex file with avrdude:
 * avrdude -p ATmega328P -b 115200 -c arduino -P [port] -U flash:w:[src hex file]

To program the generated EEPROM with avrdude use:
 * avrdude -p ATmega328P -b 115200 -c arduino -P [port] -U eeprom:w:[eeprom hex file]

 Edit src/config.c as nessicary and reflash eeprom
 
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
