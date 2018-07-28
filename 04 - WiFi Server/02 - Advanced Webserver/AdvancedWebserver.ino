#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int serverPort = 1337;
WiFiServer server(serverPort);

String prepareIndexPage() {
    String indexPage =
      String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "This is the <i>root</i> path."+
            "</html>" +
            "\r\n";
      return indexPage;
}

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
    server.begin();
    Serial.printf("[Server] Server %s is listening on Port %i", WiFi.localIP().toString().c_str(), serverPort);
}

void loop() {
    WiFiClient client = server.available();
    if(client) {
      Serial.println("[Server] Client connected to server.");
      while(client.connected()) {
        if(client.available()) {
          String line = client.readStringUntil('\r');
          if(line.length() == 1 && line[0] == '\n') {
            client.println(prepareIndexPage());
            break;
          }
        }
      }
      delay(1000);
      client.stop();
      Serial.println("[Server] Client disconnected from server.");
    }
}
