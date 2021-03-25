#include <MKRNB.h>
#include "../../src/WaziCloud.cpp"

#define PINNUMBER ""

NBClient client;
GPRS gprs;
NB nbAccess;
WaziCloud waziCloud = WaziCloud(client); 

void printWiFiStatus();

void setup() {

  Serial.begin(9600);
  while (!Serial) {;}

  Serial.println("Ready");

  boolean connected = false;

  // After starting the modem with NB.begin()
  // attach to the GPRS network with the APN, login and password
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
}

void loop() {

  if (client.available()) {
    //Send the message to WaziCloud
    waziCloud.postSensorValue("MyDevice", "TC1", "245");
  }

  delay(5000);
}

