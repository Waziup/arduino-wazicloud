
# To use this Makefile, install https://github.com/sudar/Arduino-Makefile

ARCHITECTURE = samd
ARDUINO_DIR      = /home/cdupont/Documents/workspace/arduino-1.8.10/
BOARD_TAG        = mkrwifi1010

USER_LIB_PATH    = /home/cdupont/Documents/Waziup/WaziDev/libraries
MONITOR_PORT     = /dev/ttyACM1
ARDUINO_LIBS     = ArduinoHttpClient SPI WiFiNINA WaziCloud
MONITOR_BAUDRATE = 38400 

ARDUINO_PACKAGE_DIR = /home/cdupont/.arduino15/packages/

ARDMK_DIR=/home/cdupont/Documents/workspace/Arduino-Makefile

include /home/cdupont/Documents/workspace/Arduino-Makefile/Sam.mk

monitor:
	stty -F $(MONITOR_PORT) raw $(MONITOR_BAUDRATE)
	cat $(MONITOR_PORT)
