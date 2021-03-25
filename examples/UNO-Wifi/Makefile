
# To use this Makefile, install https://github.com/sudar/Arduino-Makefile

ARDUINO_DIR      = /home/cdupont/Documents/workspace/arduino-1.8.10/
BOARD_TAG        = uno

USER_LIB_PATH    = /home/cdupont/Documents/Waziup/arduino-wazicloud/libraries
MONITOR_PORT     = /dev/ttyACM1
ARDUINO_LIBS     = SoftwareSerial SparkFunESP8266WiFi ArduinoHttpClient
MONITOR_BAUDRATE = 9600 

ARDUINO_PACKAGE_DIR = /home/cdupont/.arduino15/packages/

ARDMK_DIR=/home/cdupont/Documents/workspace/Arduino-Makefile

include /home/cdupont/Documents/workspace/Arduino-Makefile/Arduino.mk

monitor:
	stty -F $(MONITOR_PORT) raw $(MONITOR_BAUDRATE)
	cat $(MONITOR_PORT)
