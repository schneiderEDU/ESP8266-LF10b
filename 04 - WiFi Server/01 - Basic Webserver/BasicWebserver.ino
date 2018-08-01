#include <Arduino.h>
#include <ESP8266WiFi.h>
//Webserver-Library
#include <ESP8266WebServer.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

//Definition des Ports, Standardport ist 80
const int serverPort = 1337;
//Serverobjekt mit Port erzeugen
ESP8266WebServer server(serverPort);

//Funktion für Aufruf des Wurzelverzeichnisses
void handleRootPath() {
    //Sende HTTP-Antwortcode 200 (OK) und Text
    server.send(200, "text/plain", "This is the root path");
}

//Funktion für Aufruf des /alt-Pfads
void handleAltPath() {
    //Sende HTTP-Antwortcode 200 (OK) und Text
    server.send(200, "text/plain", "This is the alternative path");
}

//Funktion für Aufruf aller anderen ungültigen Pfade
void handleNotFound() {
    //Sende HTTP-Antwortcode 404 (Not found) und Text
    server.send(404, "text/plain", "The requested URL was not found on this server.");
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
    //Requesthandling für Wurzelverzeichnis
    server.on("/", handleRootPath);
    //Requesthandling für /alt - Pfad
    server.on("/alt", handleAltPath);
    //Requesthandling für alle anderen Pfade
    server.onNotFound(handleNotFound);
    //Starten des Serverdienstes
    server.begin();
    Serial.printf("[Server] Server is listening on Port %i", serverPort);
}

void loop() {
    //Behandeln eingehender Verbindungen
    server.handleClient();
}
