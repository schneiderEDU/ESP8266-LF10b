#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <detail\RequestHandlersImpl.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int serverPort = 1337;
ESP8266WebServer server(serverPort);

void handleNotFound() {
    String page = F("<html><head><title>404 Not Found</title></head><body>"
                    "<h1>Not Found</h1>"
                    "<p>The requested URL was not found on this server.</p>"
                    "</body></html>");
    server.send(404, "text/html", page);
};

void setup() {
    Serial.begin(115200);
    Serial.print("[SPIFFS] Initialising...");
    if(!SPIFFS.begin()) {
      Serial.println("failed!");
      while(1) {
        yield();
      }
    }
    else {
      Serial.println("successful!");
    }
    WiFi.begin(ssid, password);
    Serial.print("[WiFi] Connecting to WiFi ");
    Serial.print(ssid);
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println();
    Serial.print("[WiFi] Connected as ");
    Serial.println(WiFi.localIP());
    server.onNotFound(handleNotFound);
    server.serveStatic("/", SPIFFS, "/index.html");
    server.begin();
    Serial.printf("[Server] Server %s is listening on Port %i", WiFi.localIP().toString().c_str(), serverPort);
}

void loop() {
    server.handleClient();
}
