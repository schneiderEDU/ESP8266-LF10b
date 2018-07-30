#include <Arduino.h>
#include <ESP8266WiFi.h>
//Bibliothek zur Realisierung von HTTP(S)-Clients
#include <ESP8266HTTPClient.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int WAIT_DELAY = 10000;
long last_millis = -1;

//URL, die vom Client geholt werden soll
const char* url = "https://iot.schneider-edu.it/esp8266/httpsclient/test.html";
// const char* url = "http://iot.schneider-edu.it/esp8266/httpsclient/test2.html"; //connection refused
//Fingerprint des Website-Zertifikats, wird zum Verbindungsaufbau benötigt
const char* fingerprint = "e992449775c128d1d15f3e13ad81e9951e58ce65";

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
    Serial.print("Connected as ");
    Serial.println(WiFi.localIP());
}

void loop() {
  long current_millis = millis();
  if(last_millis < (current_millis-WAIT_DELAY)) {
    last_millis = current_millis;
    //Erzeuge neuen HTTPClient, kann auch für HTTPS verwendet werden
    HTTPClient client;
    Serial.println("[HTTPS] Send request...");
    //Aufbau einer verschlüsselten Verbindung zur URL unter Verwendung des Fingerprints
    client.begin(url, fingerprint);
    Serial.print("[HTTPS] GET-Request... ");
    //GET-Request, liefert HTTP-Statuscode zurück
    int responseCode = client.GET();
    if(responseCode > 0) {
      Serial.printf("Response: %d\n", responseCode);
      if(responseCode == HTTP_CODE_OK) {
        Serial.println("Content: ");
        //Auslesen der Nutzdaten (payload) der Antwort
        String payload = client.getString();
        Serial.println(payload);
      }
    }
    else {
      //Zur Diagnose im Fehlerfall
      Serial.printf("failed, Error: %s\n", client.errorToString(responseCode).c_str());
    }
    //Trennen der Verbindung
    client.end();
  }
}
