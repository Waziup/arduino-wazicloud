#include <SparkFunESP8266WiFi.h>
#include "../../src/WaziCloud.cpp"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "311-verona";   // your network SSID (name)
char pass[] = "1a2s3d4f5g";   // your network password (use for WPA, or use as key for WEP)

ESP8266Client client;
WaziCloud waziCloud = WaziCloud(client); 

void displayConnectInfo();

void setup() {

  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Ready");

  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    for(;;);
  }
  Serial.println(F("ESP8266 Shield Present. Connecting to Wifi..."));
  int retVal = esp8266.setMode(ESP8266_MODE_STA);
  if (retVal < 0)
  {
    Serial.println(F("Error connecting"));
    for(;;);
  }
  retVal = esp8266.connect(ssid, pass);
  if (retVal < 0)
  {
    Serial.println(F("Error connecting"));
    for(;;);
  }
  displayConnectInfo();
}

void loop() {

  //Send the message to WaziCloud
  waziCloud.postSensorValue("MyDevice", "TC1", "245");

  delay(5000);
}


void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // esp8266.localIP returns an IPAddress variable with the
  // ESP8266's current local IP address.
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

