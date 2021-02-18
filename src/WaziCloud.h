#ifndef wazicloud_h
#define wazicloud_h

#include <ArduinoHttpClient.h>
#include <Client.h>

class WaziCloud
{

public:
  WaziCloud(Client& client);
  void postSensorValue(const char* device_id, const char* sensor_id, const char* val);

  // The client we're using for sending HTTP requests
  Client &client;

};

#endif
