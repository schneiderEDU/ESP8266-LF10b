#include <Arduino.h>
#include <ESP8266WiFi.h>

//WiFi credentials - Festlegen der WLAN-Verbindungsdaten
const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

//IP-Adresskonfiguration
IPAddress clientIP(192, 168, 1, 100);
IPAddress netmask(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);

void setup() {
    Serial.begin(115200);
    //Verbindungsaufbau zum WLAN mittels SSID und Passwort
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    //Manuelle IP-Adresskonfiguration
    WiFi.config(clientIP, gateway, netmask, dns1, dns2);
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
