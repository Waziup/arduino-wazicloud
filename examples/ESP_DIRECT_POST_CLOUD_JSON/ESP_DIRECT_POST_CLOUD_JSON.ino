#include <ESP8266HTTPClient.h> //LIBRARY FOR HTTP
#include <ESP8266WiFi.h> //LIBRARY FOR ESP WIFI FUNCTIONALITY

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "XXXXXX"; //DEVICE ID - example 605db108af408600066050ae
const char* sensorID = "YYYYYY"; //SENSOR ID - example temperatureSensor_1
const int http_port = 443; //HTTPS PORT

void setup() {
  Serial.begin(115200); //SERIAL COMMUNICATION RATE
  
  //YOUR WIFI NAME XXXX, PASSWORD YYYY
  WiFi.begin("XXXXXX", "YYYYYY");   //ESTABLISH WIFI CONNECTION

  Serial.println("Waiting for Connection");
  
  //CODE WONT GO PAST THIS BLOCK, IF ESP DOESNT CONNECT TO WIFI
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.print(".");
  }

  //PRINT IP ADDRESS ASSIGNED TO ESP
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  
  //PARSING URL PATH - DONT TOUCH THIS
  String url = "/api/v2/devices/";
  url += devID;
  url += "/sensors/";
  url += sensorID;
  url += "/value";
  
  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS
    
    WiFiClientSecure client; //CONNECTION FOR HTTPS
    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient

    client.setInsecure(); //USING THIS BECAUSE WE DONT HAVE SSL CERTIFICATE FINGERPRINT
    
    http.begin(client ,host ,http_port ,url);      //SPECIFY REQUEST DESTINATION
     http.addHeader("Content-Type", "application/json;charset=utf-8");  //SPECIFY CONTENT TYPE
 
    int value = 23; //SENDING VALUES TO THE CLOUD - e.g sending a dummy value of 23
    char body[20]; //HOLDS JSON DATA
    sprintf( body, "{\"value\": %d}", value);//PARSING & FORMATTING DATA
    
    int httpCode = http.POST(body); //SENDING JSON DATA
    
    // HTTP CODE WILL BE NEGATIVE IF THERE'S AN ERROR
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // FILE FOUND ON SERVER
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();  //CLOSING HTTP CONNECTION
 
  } else {
    Serial.println("WiFi Connection Fail");//IF ESP CAN'T CONNECTED TO WIFI
  }
  
  delay(30000);  //SENDING SENSOR DATA EVERY 30 SECONDS
}
