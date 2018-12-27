#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>


//WiFi credentials - Festlegen der WLAN-Verbindungsdaten
const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";
//Name, auf den später per DNS aufgelöst werden soll
const char* name = "myesp";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  //Ausgabe bei einer erfolgreichen Verbindung, inkl. vom DHCP-Server erhaltenen IP-Adresse
  Serial.print("Connected as ");
  Serial.println(WiFi.localIP());
  Serial.print("Starting mDNS responder...");
  //mDNS responder starten, bei Erfolg löst dieser auf myesp.local auf
  if(!MDNS.begin(name)) {
    Serial.println("failed!");
  }
  else {
    Serial.println("successful!");
    Serial.print("Name: ");
    Serial.print(name);
    Serial.println(".local");
  }
}

void loop() {

}
