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
  unsigned long ultimeout = millis()+250;
  while(!client.available() && (millis()<ultimeout) )
  {
    delay(1);
  }
  if(millis()>ultimeout)
  {
    Serial.println("A client timed out!");
    return;
  }
  String sRequest = client.readStringUntil('\r');
  client.flush();
  if (sRequest == "") {
    Serial.println("Request was empty! - Stopping client now!");
    client.stop();
    return;
  }
  String sPath = "", sParam = "", sCmd = "";
  String sGetStart  = "GET ";
  int iStart, iEndSpace, iEndQuest;
  iStart = sRequest.indexOf(sGetStart);
  if(iStart >= 0) {
    iStart +=+ sGetStart.length();
    iEndSpace = sRequest.indexOf(" ", iStart);
    iEndQuest = sRequest.indexOf("?", iStart);

    if(iEndSpace > 0) {
      if(iEndQuest > 0) {
        sPath = sRequest.substring(iStart, iEndQuest);
        sParam = sRequest.substring(iEndQuest, iEndSpace);
      }
      else {
        sPath = sRequest.substring(iStart, iEndSpace);
      }
    }
  }
  if(sParam.length()>0)
  {
    int sEqu=sParam.indexOf("=");
    if(sEqu>=0)
    {
      sCmd = sParam.substring(sEqu+1,sParam.length());
      Serial.println(sCmd);
    }
  }
  String sResponse, sHeader;
  if(sPath!="/") {
    sResponse="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  else {
    sResponse  = "<html><head><title>WeMos Relay Switch</title>";
    sResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\"></head><body>";
    sResponse += "<h1>WeMos Relay Switch</h1>";
    sResponse += "<p>Relay on D1 <a href=\"?relay=ON\"><button>On</button></a>&nbsp;<a href=\"?relay=OFF\"><button>Off</button></a></p></body></html>";

    if (sCmd.length() > 0)
    {
      if(sCmd.indexOf("ON") >= 0) {
        digitalWrite(relayPin, 1);
      }
      else if(sCmd.indexOf("OFF") >= 0)
      {
        digitalWrite(relayPin, 0);
      }
    }

    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  client.print(sHeader);
  client.print(sResponse);
}
