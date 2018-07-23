#include <Arduino.h>
#include <ESP8266WiFi.h>

const int WAIT_DELAY = 10000;
long last_millis = -1;

//WiFi credentials - Festlegen der Verbindungsdaten und -parameter für die Clients
const char* ssid = "MyOwnAP";
const char* password = "mysupersecretpassword";
const int channel = 6;
const bool hidden = false;

//IP-Adresskonfiguration
IPAddress localIP(192, 168, 1, 100);
IPAddress netmask(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);

void setup() {
    Serial.begin(115200);
    Serial.print("Setting up AP configuration...");
    //IP-Adresskonfiguration des Access Points; gibt bei Erfolg true zurück
    if(WiFi.softAPConfig(localIP, gateway, netmask)) {
      Serial.println("successful!");
    }
    else {
      Serial.println("failed!");
    }
    Serial.print("Setting AP mode...");
    //Versetzt den ESP in den AP mode und öffnet ein WLAN mit festgelegter SSID und Passwort; gibt bei Erfolg true zurück
    if(WiFi.softAP(ssid, password, channel, hidden)) {
      Serial.println("successful!");
    }
    else {
      Serial.println("failed!");
    }
    Serial.print("AP IP address: ");
    //Gibt die IP-Adresse des ESP-APs zurück, normalerweise 192.168.4.1
    Serial.println(WiFi.softAPIP());
  }

void loop() {
    long current_millis = millis();
    if(last_millis < (current_millis-WAIT_DELAY)) {
      last_millis = current_millis;
      Serial.print("Connected clients: ");
      //Gibt die Anzahl der verbundenen Clients zurück
      Serial.println(WiFi.softAPgetStationNum());
    }
}
