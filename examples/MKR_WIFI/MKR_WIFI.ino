#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <WaziCloud.h>

char ssid[] = "311-verona";   // your network SSID (name)
char pass[] = "1a2s3d4f5g";   // your network password (use for WPA, or use as key for WEP)

WiFiClient client;
WaziCloud waziCloud = WaziCloud(client); 

void printWiFiStatus();

void setup() {

  Serial.begin(9600);
  while (!Serial) {;}

  Serial.println("Ready");
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  // attempt to connect to WiFi network:
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connected to wifi");
  printWiFiStatus();
}

void loop() {

  //Send the message to WaziCloud
  waziCloud.postSensorValue("MyDevice", "TC", "25");

  delay(5000);
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
