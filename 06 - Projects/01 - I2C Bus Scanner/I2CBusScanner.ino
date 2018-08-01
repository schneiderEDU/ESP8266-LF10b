#include <Arduino.h>
#include <Wire.h>

#define SCL D1
#define SDA D2

const int DELAY = 60000;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA, SCL);
    Serial.println("I2C-Bus-Scanner");
    Serial.print("SDA: ");
    Serial.println(SDA);
    Serial.print("SCL: ");
    Serial.println(SCL);
}

void loop() {
    byte errorCode, busAddress;
    int countDevices = 0;
    Serial.println("Scanning...");
    for(busAddress = 1; busAddress < 127; busAddress++) {
      Wire.beginTransmission(busAddress);
      errorCode = Wire.endTransmission();
      if(errorCode == 0) {
        Serial.print("I2C device found at address 0x");
        if(busAddress < 16) Serial.print("0");
        Serial.println(busAddress, HEX);
        countDevices++;
      }
      else if(errorCode == 4) {
        Serial.print("Unknown error at address 0x");
        if(busAddress < 16) Serial.print("0");
        Serial.println(busAddress, HEX);
      }
    }
    if(countDevices == 0) {
      Serial.println("No I2C devices found. Check wiring!");
    }
    else {
      Serial.printf("Scan completed. %i devices found.", countDevices);
    }
    delay(DELAY);
}
