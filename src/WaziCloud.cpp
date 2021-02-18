#include "WaziCloud.h"

char server[] = "api.waziup.io";
char resource[]   = "/api/v2/devices/MyDevice/sensors/TC/value"; 
char contentType[] = "text/plain;charset=utf-8";
int port = 80; 

WaziCloud::WaziCloud(Client& aClient) : client(aClient) {
}

void WaziCloud::postSensorValue(const char* device_id, const char* sensor_id, const char* val) {
 
  HttpClient httpClient = HttpClient(client, server, port);
  Serial.print("Posting value...");
  //Send the message to WaziCloud
  httpClient.post(resource, contentType, val);
  Serial.print("Done");
  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println("POST finished."); 
  
}
