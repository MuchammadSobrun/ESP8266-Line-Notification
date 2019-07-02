/*Smart Shoes*/
// By: The Mega Robotics
//Last Modify : 20/09/2017

void Line_Notify(String message) ;

#include <ESP8266WiFi.h>

// Config connect WiFi
#define WIFI_SSID "Indonesian"        //Wifi name
#define WIFI_PASSWORD "12345678"  //Wifi Password

// Line config
#define LINE_TOKEN "N02f5MntstZNb1gqxt05HrKJXUilR9pIMn0QBwUBtGn" //Qkp46hieyAApxcAwAsGBmz5S0ZCFxghsIPkrng5C4w5// smart shoes ..... //RIiwRm7O8yQr2mgW8kTa5WnuVMOxkwvxT6tL93yp7Ck Accident

#define SW 4

String message = "This%20is%20for%20testing%20only";
//String message = "Your%20family%20need%20your%20help%2C%20call%20Police%20or%20emergency%20call.%0APolice%20Number%20%3A%20191%0AAmbulance%20and%20Rescue%20%3A%201554%0A%0Aidentity%3A%20%0AName%20%3A%20Mr.Muchammad%20Sobrun%20Ibnu%20Atfal%0APosition%20%3A%20Pattanakarn%20Rd.%0A";



void setup() {
  
  pinMode(SW, INPUT);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}


void loop() {
//  Serial.available();
//  char a = Serial.read();
//  //Serial.println("Ready");
//  
//  if (a == 'a') {
//    Serial.println("Enter !");
//    Line_Notify(message);
//    // Serial.println();
//  }
  if (digitalRead(SW) == HIGH) {
    while(digitalRead(SW) == HIGH) delay(10);

    Serial.println("Enter !");
    Line_Notify(message);
    // Serial.println();
  }
  
  delay(10);
}


void Line_Notify(String message) {
  WiFiClientSecure client;
  client.setInsecure();
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  Serial.println("-------------");
}
