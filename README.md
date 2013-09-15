To build the generated elf into an intel hex file use avr-objcopy:
	avr-objcpy -Oihex [src file] [dest file]
avrdude:
	upload protocol=arduino
	upload speed=115200
