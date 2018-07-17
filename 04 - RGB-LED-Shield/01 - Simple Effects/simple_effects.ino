#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN    D4
#define NUMPIX  7

Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIX, PIN, NEO_GRB + NEO_KHZ800);

//Helper function: turns all leds off
void allOff() {
  for(int i = 0; i < NUMPIX; i++) {
    led.setPixelColor(i, 0);
  }
  led.show();
}

//Helper function: set all leds to a specific color
void setAll(uint32_t c) {
  for(int i = 0; i < NUMPIX; i++) {
    led.setPixelColor(i, c);
  }
  led.show();
}

//fan-like rotation effect
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

//pulse effect
void pulse(uint32_t color) {
    //converting from unsigned integer to rgb values
    byte red   = (byte)(color >> 16);
    byte green = (byte)(color >>  8);
    byte blue  = (byte)(color >>  0);
    float r,g,b;
    for(int i = 0; i < 256; i++) {
      r   = (i/256.0)*red;
      g   = (i/256.0)*green;
      b   = (i/256.0)*blue;
      setAll(led.Color(r, g, b));
      delay(10);
    }
    for(int i = 256; i > 0; i--) {
      r   = (i/256.0)*red;
      g   = (i/256.0)*green;
      b   = (i/256.0)*blue;
      setAll(led.Color(r, g, b));
      delay(10);
    }
}

//strobe effect
void strobe(uint32_t color, int flashCount, int flashDelay) {
  for(int i = 0; i < flashCount; i++) {
    setAll(color);
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
    rotation(led.Color(255, 15, 223), 1000);
    pulse(led.Color(255, 15, 223));
    strobe(led.Color(255, 15, 223), 50, 50);
}
