#include <Arduino.h>
#include <ESP8266WiFi.h>

const int WAIT_DELAY = 60000;
long last_millis = -1;

//Funktion zur Ausgabe der gefundenen WLANs
void showFoundNetworks(int numNetworks) {
  Serial.printf("%d networks found\n", numNetworks);
  Serial.println("--------------------------");
  //Iteriere über die Liste der gefundenen Drahtlosnetzwerke
  for(int i = 0; i < numNetworks; i++) {
    String encType;
    //Betrachte den Verschlüsselungstyp des aktuellen Drahtlosnetzwerks
    if(WiFi.encryptionType(i) == ENC_TYPE_NONE) {
      encType = "open";
    }
    else if (WiFi.encryptionType(i) == ENC_TYPE_WEP) {
      encType = "WEP";
    }
    else if (WiFi.encryptionType(i) == ENC_TYPE_TKIP) {
      encType = "WPA/TKIP";
    }
    else if (WiFi.encryptionType(i) == ENC_TYPE_CCMP) {
      encType = "WPA2/PSK";
    }
    else {
      encType = "WPA/WPA2/PSK";
    }
    String isHidden;
    //Betrachte die Sichtbarkeit des aktuelle Drahtlosnetzwerks
    if(WiFi.isHidden(i) == true) {
      isHidden = "hidden";
    }
    else {
      isHidden = "visible";
    }
    //Formatierte Ausgabe aller Informationen über das aktuelle Drahtlosnetzwerk
    Serial.printf("Network %d: %s, Channel: %d (%ddBm) %s - %s\n",
                    i+1,
                    WiFi.SSID(i).c_str(),
                    WiFi.channel(i),
                    WiFi.RSSI(i),
                    encType.c_str(),
                    isHidden.c_str());
  }
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  long current_millis = millis();
  if(last_millis < (current_millis-WAIT_DELAY)) {
    last_millis = current_millis;
    //Versetzt das WLAN in den Station-Modus
    WiFi.mode(WIFI_STA);
    //Trennt alle aktiven Drahtlosverbindungen
    WiFi.disconnect();
    delay(100);
    //Beginne asynchron nach Drahtlosnetzwerken zu scannen,
    //führe nach Beendigung die Funktion showFoundNetworks() aus
    //und beziehe versteckte Netzwerke mit in den Scan ein (true)
    WiFi.scanNetworksAsync(showFoundNetworks, true);
    //Löscht die Ergebnisse des letzten Scans
    WiFi.scanDelete();
  }
}
