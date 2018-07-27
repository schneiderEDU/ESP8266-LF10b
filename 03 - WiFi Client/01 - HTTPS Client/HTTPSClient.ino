#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int WAIT_DELAY = 10000;
long last_millis = -1;

const char* url = "https://iot.schneider-edu.it/esp8266/httpclient/test.html";
// const char* url = "http://iot.schneider-edu.it/esp8266/httpclient/test2.html"; //connection refused
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
    HTTPClient client;
    Serial.println("[HTTP] Sende Anfrage...");
    client.begin(url, fingerprint);
    Serial.print("[HTTP] GET-Request... ");
    int responseCode = client.GET();
    if(responseCode > 0) {
      Serial.printf("Antwort: %d\n", responseCode);
      if(responseCode == HTTP_CODE_OK) {
        Serial.println("Antwort des Servers: ");
        String payload = client.getString();
        Serial.println(payload);
      }
    }
    else {
      Serial.printf("fehlgeschlagen, Fehler: %s\n", client.errorToString(responseCode).c_str());
    }
    client.end();
  }
}
