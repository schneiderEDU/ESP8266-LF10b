#include <Arduino.h>
#include <ESP8266WiFi.h>

//WiFi credentials - Festlegen der WLAN-Verbindungsdaten
const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

void setup() {
    Serial.begin(115200);
    //Verbindungsaufbau zum WLAN mittels SSID und Passwort
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    //Warten bis Verbindung aufgebaut ist
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println();
    //Ausgabe bei einer erfolgreichen Verbindung, inkl. vom DHCP-Server erhaltenen IP-Adresse
    Serial.print("Connected as ");
    Serial.println(WiFi.localIP());
}

void loop() {

}
