#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int serverPort = 1337;
ESP8266WebServer server(serverPort);

void handleRootPath() {
    server.send(200, "text/plain", "This is the root path");
}

void handleAltPath() {
    server.send(200, "text/plain", "This is the alternative path");
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
    server.on("/", handleRootPath);
    server.on("/alt", handleAltPath);
    server.begin();
    Serial.printf("[Server] Server is listening on Port %i", serverPort);
}

void loop() {
    server.handleClient();
}
