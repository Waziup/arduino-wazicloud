#include <ESP8266HTTPClient.h> //LIBRARY FOR HTTP
#include <ESP8266WiFi.h> //LIBRARY FOR ESP FUNCTIONALITY

const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "605db108af408600066050ae"; //DEVICE ID - example 605db108af408600066050ae
const char* sensorID = "temperatureSensor_1"; //SENSOR ID - example temperatureSensor_1
const int http_port = 80; //HTTP PORT

//const int relay_pin = 2; //RELAY PIN NUMBER

void setup() {
  Serial.begin(115200); //SERIAL COMMUNICATION
  //pinMode(relay_pin, OUTPUT); //DECLARING RELAY PIN AS OUTPUT
  
  //YOUR WIFI NAME XXXX, PASSWORD YYYY
  WiFi.begin("Hive_Coworking", "sg@6Fb7c06M");   //ESTABLISH WIFI CONNECTION

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

  //PARSING URL PATH - DONT TOUCH THIS
  String url = "/api/v2/devices/";
  url += devID;
  url += "/sensors/";
  url += sensorID;
  
  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS
 
    HTTPClient http;    //DECLARE OBJECT OF CLASS HTTPClient
 
    http.begin(host,http_port, url);      //SPECIFY REQUEST DESTINATION
 
    int httpCode = http.GET();   //GETTING RETURN CODE
    Serial.println(httpCode);   //PRINT HTTP RETURN CODE
    
    if (httpCode > 0) { //MAKING SURE THERE WAS A RESPONSE
       // Get the request response payload
       String payload = http.getString(); //ASSIGNING THE DATA RECEIVED TO THE PAYLOAD VARIABLE
        
       // TODO: Parsing
       Serial.println(payload); //PRINTING THE DATA RECEIVED
       Serial.println();

       /*
       //SUBSTRINGING TO GET THE NEEDED VALUE IN THE PAYLOAD
       int strt_p = payload.lastIndexOf("value") + 7;
       int end_p = payload.indexOf("timestamp") - 2;
       String control = payload.substring(strt_p, end_p);
       Serial.println(control);
  
       if(control.equals("1")){ //RELAY ON IF VALUE IS 1
          digitalWrite(relay_pin, HIGH);
       }else if(control.equals("0")){ //RELAY OFF IF VALUE IS 0
          digitalWrite(relay_pin, LOW);
       }
        */
    }
    Serial.println("Closing Connection");
    http.end();   //Close connection
    Serial.println();
  }
  delay(5000);  //SEND REQUEST EVERY 5 SECONDS
}
