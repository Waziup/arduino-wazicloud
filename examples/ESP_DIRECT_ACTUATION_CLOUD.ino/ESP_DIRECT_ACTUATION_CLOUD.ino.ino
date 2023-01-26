#include <ESP8266HTTPClient.h> //LIBRARY FOR HTTP
#include <ESP8266WiFi.h> //LIBRARY FOR ESP WIFI FUNCTIONALITY

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "XXXXXX"; //DEVICE ID - example 605db108af408600066050ae
const char* actuatorID = "YYYYYY"; //ACTUATOR ID - example actuator_1

const int http_port = 443; //HTTPS PORT

const int relay_pin = 16;//ACTUATOR PIN D0 IS GPIO 16

void setup() {
  Serial.begin(115200); //SERIAL COMMUNICATION RATE
  pinMode(relay_pin, OUTPUT); //DECLARING PIN FUNCTION

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
  url += "/actuators/";
  url += actuatorID;

  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS

    WiFiClientSecure client; //CONNECTION FOR HTTPS
    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient

    client.setInsecure(); //USING THIS BECAUSE WE DONT HAVE SSL CERTIFICATE FINGERPRINT

    http.begin(client , host , http_port , url);   //SPECIFY REQUEST DESTINATION

    int httpCode = http.GET(); //GETTING JSON DATA

    // HTTP CODE WILL BE NEGATIVE IF THERE'S AN ERROR
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // FILE FOUND ON SERVER
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");

        //SUBSTRINGING TO GET THE NEEDED VALUE IN THE PAYLOAD
        int strt_p = payload.lastIndexOf("value") + 7;
        int end_p = payload.indexOf("actuator_kind") - 2;
        String control = payload.substring(strt_p, end_p);
        Serial.println(control);

        if (control.equals("true")) { //RELAY ON IF VALUE IS TRUE
          digitalWrite(relay_pin, HIGH);
        } else if (control.equals("false")) { //RELAY OFF IF VALUE IS FALSE
          digitalWrite(relay_pin, LOW);
        }
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();  //CLOSING HTTP CONNECTION

  } else {
    Serial.println("WiFi Connection Fail");//IF ESP CAN'T CONNECTED TO WIFI
  }

  delay(5000);  //CHECK FOR SWITCH DATA EVERY 5 SECONDS
}
