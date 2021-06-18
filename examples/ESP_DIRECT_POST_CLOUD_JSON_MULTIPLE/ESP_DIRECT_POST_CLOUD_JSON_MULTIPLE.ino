#include <ESP8266HTTPClient.h> //LIBRARY FOR HTTP
#include <ESP8266WiFi.h> //LIBRARY FOR ESP FUNCTIONALITY

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "XXXX"; //DEVICE ID - example 605db108af408600066050ae
const int http_port = 80; //HTTP PORT

void setup() {
  Serial.begin(115200); //SERIAL COMMUNICATION

  //YOUR WIFI NAME XXXX, PASSWORD YYYY
  WiFi.begin("XXXX", "YYYY");   //ESTABLISH WIFI CONNECTION

  Serial.println("Waiting for Connection");

  //IF WIFI DOESNT CONNECT CODE WONT GO PAST THIS BLOCK
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
    //XXXX IS SENSOR ID - example temperatureSensor_1
    send_to_cloud("XXXX/value", 23); //SENDING SENSOR 1 DATA e.g sending a dummy value of 23
    
    delay(500);
    
    //YYYY IS SENSOR ID - example humiditySensor_1
    send_to_cloud("YYYY/value" , 25); //SENDING SENSOR 2 DATA e.g sending a dummy value of 25
    
    delay(10000);  //SEND REQUEST EVERY 10 SECONDS
}

void send_to_cloud(String u, int data){
  
   //PARSING URL PATH - DONT TOUCH THIS
    String url = "/api/v2/devices/";
    url += devID;
    url += "/sensors/";
    url += u;
    
  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS

    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient

    http.begin(host, http_port, u);     //SPECIFY REQUEST DESTINATION
    http.addHeader("Content-Type", "application/json;charset=utf-8");  //SPECIFY CONTENT TYPE

    int value = data; //SENDING VALUES TO THE CLOUD
    char body[20]; //PARSING DATA
    sprintf( body, "{\"value\": %d}", value);//PARSING DATA

    int httpCode = http.POST(body); //SENDING JSON VALUE
    String payload = http.getString(); //GETTING RESPONSE PAYLOAD

    Serial.println(httpCode);   //PRINT HTTP RETURN CODE
    Serial.println(payload);    //PRINT PAYLOAD RESPONSE

    http.end();  //CLOSING HTTP CONNECTION

  } else {
    Serial.println("WiFi Connection Fail");
  }
}
