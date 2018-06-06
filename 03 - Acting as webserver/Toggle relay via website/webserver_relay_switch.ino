#include <ESP8266WiFi.h>

const int relayPin = D1;

const char* ssid = "MyWeMosWLAN";
const char* pass = "supersecurepassword";

WiFiServer server(80);

void setup() {
  pinMode(relayPin, OUTPUT);

  Serial.begin(115200);

  IPAddress address (192, 168, 100, 1);
  IPAddress netmask (255, 255, 255, 0);
  IPAddress gateway (192, 168, 100, 1);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(address, gateway, netmask);
  WiFi.softAP(ssid, pass);
  Serial.println("AP IP address configuration");
  Serial.println("---------------------------");
  Serial.print  ("address: ");
  Serial.println(address);
  Serial.print  ("netmask: ");
  Serial.println(netmask);
  Serial.print  ("gateway: ");
  Serial.println(gateway);

  server.begin();
}
void loop() {
  WiFiClient client = server.available();
  if(!client) {
    return;
  }
  Serial.println("A new client has connected.");
  String request = client.readStringUntil('\r');
  client.flush();
  if (request == "") {
    Serial.println("Request was empty! - Stopping client now!");
    client.stop();
    return;
  }
  String path = "", param = "", cmd = "";
  String getStart  = "GET ";
  int start, endSpace, endQuest;
  start = request.indexOf(getStart);
  if(start >= 0) {
    start +=+ getStart.length();
    endSpace = request.indexOf(" ", start);
    endQuest = request.indexOf("?", start);

    if(endSpace > 0) {
      if(endQuest > 0) {
        path = request.substring(start, endQuest);
        param = request.substring(endQuest, endSpace);
      }
      else {
        path = request.substring(start, endSpace);
      }
    }
  }
  if(param.length()>0)
  {
    int equ=param.indexOf("=");
    if(equ>=0)
    {
      cmd = param.substring(equ+1,param.length());
      Serial.println(cmd);
    }
  }
  String response, header;
  if(path!="/") {
    response="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    header  = "HTTP/1.1 404 Not found\r\n";
    header += "Content-Length: ";
    header += response.length();
    header += "\r\n";
    header += "Content-Type: text/html\r\n";
    header += "Connection: close\r\n";
    header += "\r\n";
  }
  else {
    response  = "<html><head><title>WeMos Relay Switch</title>";
    response += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\"></head><body>";
    response += "<h1>WeMos Relay Switch</h1>";
    response += "<p>Relay on D1 <a href=\"?relay=ON\"><button>On</button></a>&nbsp;<a href=\"?relay=OFF\"><button>Off</button></a></p></body></html>";

    if (cmd.length() > 0)
    {
      if(cmd.indexOf("ON") >= 0) {
        digitalWrite(relayPin, 1);
      }
      else if(cmd.indexOf("OFF") >= 0)
      {
        digitalWrite(relayPin, 0);
      }
    }

    header  = "HTTP/1.1 200 OK\r\n";
    header += "Content-Length: ";
    header += response.length();
    header += "\r\n";
    header += "Content-Type: text/html\r\n";
    header += "Connection: close\r\n";
    header += "\r\n";
  }
  client.print(header);
  client.print(response);
  client.stop();
  Serial.println("Client disconnected!");
}
