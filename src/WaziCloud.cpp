#include "WaziCloud.h"

char server[] = "api.waziup.io";
char contentType[] = "text/plain;charset=utf-8";
int port = 80; 

WaziCloud::WaziCloud(Client& aClient) : client(aClient) {
}

void WaziCloud::postSensorValue(const char* device_id, const char* sensor_id, const char* val) {
 
  HttpClient httpClient = HttpClient(client, server, port);
  Serial.print("Posting value...");

  char path[256];
  snprintf(path, sizeof path, "%s%s%s%s%s", "/api/v2/devices/", device_id, "/sensors/", sensor_id, "/value");
  Serial.print("Path: ");
  Serial.println(path);
  //Send the message to WaziCloud
  httpClient.post(path, contentType, val);
  Serial.println("Done");
  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println("POST finished."); 
  
}
