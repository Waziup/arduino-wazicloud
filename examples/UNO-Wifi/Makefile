# To use this Makefile, install https://github.com/sudar/Arduino-Makefile

ARDUINO_DIR      = /home/cdupont/Documents/workspace/arduino-1.8.10/
BOARD_TAG        = uno
MONITOR_PORT     = /dev/ttyACM1
ARDUINO_LIBS     = SoftwareSerial SparkFunESP8266WiFi ArduinoHttpClient
MONITOR_BAUDRATE = 9600 

include ../../.env
include /home/cdupont/Documents/workspace/Arduino-Makefile/Arduino.mk

monitor:
	stty -F $(MONITOR_PORT) raw $(MONITOR_BAUDRATE)
	cat $(MONITOR_PORT)
