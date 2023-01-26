#include <ESP8266HTTPClient.h> //LIBRARY FOR HTTP
#include <ESP8266WiFi.h> //LIBRARY FOR ESP WIFI FUNCTIONALITY

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "XXXXXX"; //DEVICE ID - example 605db108af408600066050ae
const int http_port = 443; //HTTPS PORT

const char* sensorID_1 = "YYYYYY"; //SENSOR 1 ID - example temperatureSensor_1
const char* sensorID_2 = "ZZZZZZ"; //SENSOR 2 ID - example temperatureSensor_2


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
  
  send_to_cloud(sensorID_1, 24); //SEDNING SENSOR 1 DATA

  delay(2000);  //WAIT 2 SECONDS

  send_to_cloud(sensorID_2, 20.5); //SEDNING SENSOR 2 DATA
  
  delay(10000); //SENDING SENSOR DATA EVERY 10 SECONDS
}


void send_to_cloud(String sens_id, int sense_val) {
  
  //PARSING URL PATH - DONT TOUCH THIS
  String url = "/api/v2/devices/";
  url += devID;
  url += "/sensors/";
  url += sens_id;
  url += "/value";
  
  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS
    
    WiFiClientSecure client; //CONNECTION FOR HTTPS
    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient

    client.setInsecure(); //USING THIS BECAUSE WE DONT HAVE SSL CERTIFICATE FINGERPRINT
    
    http.begin(client ,host ,http_port ,url);      //SPECIFY REQUEST DESTINATION
     http.addHeader("Content-Type", "application/json;charset=utf-8");  //SPECIFY CONTENT TYPE
 
    int value = sense_val; //SENDING VALUES TO THE CLOUD
    char body[20]; //TO HOLD JSON DATA
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
}
