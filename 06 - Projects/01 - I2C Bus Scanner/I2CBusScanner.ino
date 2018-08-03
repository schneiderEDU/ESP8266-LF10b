#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//I2C
#define SCL D1
#define SDA D2

//WiFi
const char* ssid = "UPC554A57E";
const char* password = "Yx6p7ywmurew";

//SearchResults
String deviceString;

//Webserver
const int serverPort = 80;
ESP8266WebServer server(serverPort);

//Helper method to convert decimal value to hex string
String decToHex(int decValue) {
  String hexValue;
  bool lowerSixteen = false;
  if(decValue < 16) lowerSixteen = true;
  while(decValue > 0) {
    int mod = decValue%16;
    if(mod < 10) {
      hexValue = String(mod) + hexValue;
    }
    else if (mod == 10) {
      hexValue = "a" + hexValue;
    }
    else if (mod == 11) {
      hexValue = "b" + hexValue;
    }
    else if (mod == 12) {
      hexValue = "c" + hexValue;
    }
    else if (mod == 13) {
      hexValue = "d" + hexValue;
    }
    else if (mod == 14) {
      hexValue = "e" + hexValue;
    }
    else if (mod == 15) {
      hexValue = "f" + hexValue;
    }
    decValue /= 16;
  }
  if (lowerSixteen) hexValue = "0" + hexValue;
  return hexValue;
}

//Connect to Wifi
void connectWiFi() {
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
  Serial.println();
}

//Check if an i2c device is present at the given address
int checkAddress(int& address) {
  byte errorCode, busAddress;
  int deviceFound = 0;
  busAddress = (byte) address;
  Wire.beginTransmission(busAddress);
  errorCode = Wire.endTransmission();
  if(errorCode == 0) {
    deviceFound = 1;
  }
  else if (errorCode == 4) {
    deviceFound = 2;
  }
  return deviceFound;
}

//Searches for devices and return the results as HTML page
String searchDevices() {
  int countDevices = 0;
  int countErrors = 0;
  deviceString = "<html><body><head><title>I2C Scanner</title></head><h1>I2C Scanner</h1><p><h3>Wiring</h3>SDA: "+ String(SDA) +"<br/>SCL: "+ String(SCL) + " </p><p><h3>Scan results</h3><ul>";
  for (int i = 0; i < 127; i++) {
    if(checkAddress(i) != 0) {
      if(checkAddress(i) == 1) {
        deviceString = deviceString + "<li>I2C device found ";
        countDevices++;
      }
      else {
        deviceString = deviceString + "<li>Unknown error ";
        countErrors++;
      }
      deviceString = deviceString + "at address 0x" + decToHex(i)  + "</li>";
    }
  }
  deviceString += "</ul></p>";
  deviceString += "<p>Scan completed. " + String(countDevices) + " device";
  if (countDevices != 1) deviceString += "s";
  deviceString += " found. " + String(countErrors) + " error";
  if (countErrors != 1) deviceString += "s";
  deviceString += " occured.</p><button onClick=\"window.location.reload()\">Scan again</button></body><html>";
  return deviceString;
}

void handleRootPath() {
    server.send(200, "text/html", searchDevices());
}

void handleNotFound() {
    String page = F("<html><head><title>404 Not Found</title></head><body>"
                    "<h1>Not Found</h1>"
                    "<p>The requested URL was not found on this server.</p>"
                    "</body></html>");
    server.send(404, "text/html", page);
};

void setup() {
    Serial.begin(115200);
    connectWiFi();
    Wire.begin(SDA, SCL);
    server.on("/", handleRootPath);
    server.onNotFound(handleNotFound);
    server.begin();
}

void loop() {
    server.handleClient();
}
