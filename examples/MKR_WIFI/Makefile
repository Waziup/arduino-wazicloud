
# To use this Makefile, install https://github.com/sudar/Arduino-Makefile

ARCHITECTURE     = samd
BOARD_TAG        = mkrwifi1010
MONITOR_PORT     = /dev/ttyACM1
ARDUINO_LIBS     = ArduinoHttpClient SPI WiFiNINA
MONITOR_BAUDRATE = 38400 


include ../../.env
include /home/cdupont/Documents/workspace/Arduino-Makefile/Sam.mk

monitor:
	stty -F $(MONITOR_PORT) raw $(MONITOR_BAUDRATE)
	cat $(MONITOR_PORT)
