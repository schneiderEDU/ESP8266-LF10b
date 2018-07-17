#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN    D4
#define NUMPIX  7

Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIX, PIN, NEO_GRB + NEO_KHZ800);

void allOff() {
  for(int i = 0; i < NUMPIX; i++) {
    led.setPixelColor(i, 0);
  }
  led.show();
}

void setAll(int r, int g, int b) {
  for(int i = 0; i < NUMPIX; i++) {
    led.setPixelColor(i, r, g, b);
  }
  led.show();
}


void rotation(uint32_t color, int time) {
    led.setPixelColor(0, color);
    for(int i=1; i<=(int)NUMPIX/2; i++) {
      led.setPixelColor(i, color);
      led.setPixelColor(i+3, color);
      led.show();
      delay(time);
      led.setPixelColor(i, 0);
      led.setPixelColor(i+3, 0);
    }
}

void pulse(byte r, byte g, byte b) {
    led.setPixelColor(0, 0);
    led.show();
    float red, green, blue;
    for(int i = 0; i < 256; i++) {
      red   = (i/256.0)*r;
      green = (i/256.0)*g;
      blue  = (i/256.0)*b;
      setAll(red, green, blue);
      delay(10);
    }
    for(int i = 256; i > 0; i--) {
      red   = (i/256.0)*r;
      green = (i/256.0)*g;
      blue  = (i/256.0)*b;
      setAll(red, green, blue);
      delay(10);
    }
}

void strobe(byte r, byte g, byte b, int flashCount, int flashDelay) {
  for(int i = 0; i < flashCount; i++) {
    setAll(r, g, b);
    delay(flashDelay);
    allOff();
    delay(flashDelay);
  }
}

void setup() {
    led.begin();
    led.show();
}

void loop() {
    led.setBrightness(64);
    rotation(led.Color(50,0,0), 1000);
    pulse(0xFF, 0x0F, 0xDF);
    strobe(0xFF, 0x0F, 0xDF, 50, 50);
}
