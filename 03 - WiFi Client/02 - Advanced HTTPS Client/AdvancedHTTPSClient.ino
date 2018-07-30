#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int WAIT_DELAY = 10000;
long last_millis = -1;

//Verbindungsdaten des Servers
const char* domain = "iot.schneider-edu.it";
const String doc = "/esp8266/httpsclient/test.html"
const char* fingerprint = "e992449775c128d1d15f3e13ad81e9951e58ce65";
const int httpsPort = 443;

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
    //Erzeugen eines WiFiClientSecure-Objekts
    WiFiClientSecure client;
    Serial.print("[HTTPS] Connecting... ");
    //Aufbau der Verbindung zum Server
    if(!client.connect(domain, httpsPort)) {
      Serial.println("failed");
      return;
    }
    else {
      Serial.println("successful");
      Serial.print("[HTTPS] Checking certificate... ");
      //Überprüfung der Integrität des Servers mittels Zertifikat
      if(!client.verify(fingerprint, domain)) {
        Serial.println("failed");
        return;
      }
      else {
        Serial.println("successful");
        Serial.print("[HTTPS] Sending request... ");
        //Schreiben des GET-Requests an den Server
        client.print(String("GET ") + doc + " HTTP/1.1\r\n" +
             "Host: " + domain + "\r\n" +
             "User-Agent: AdvancedHTTPSClientOnESP8266\r\n" +
             "Connection: close\r\n\r\n");
        Serial.println("done");
      }
      //Auswerten der Serverantwort
      while (client.connected()) {
        //Empfangen der Headerdaten
        String line = client.readStringUntil('\n');
        if(line == "\r") {
          Serial.println("[Response] receiving headers DONE!");
        }
        //Empfangen der Nutzdaten
        Serial.print("[Response] ");
        Serial.println(line);
      }
      Serial.println("[HTTPS] Closing connection... successful");
      delay(1000);
    }
  }
}
