#include <Arduino.h>

//Wartezeit in Millisekunden
const int WAIT_DELAY = 1000;
//Zeit des letzten Durchlaufs
long last_millis = -1;

void setup() {
    Serial.begin(115200);
}

void loop() {
    //Hole aktuelle Millisekunden seit Start
    long current_millis = millis();
    //Wenn die Zeit des letzten Durchlaufs kleiner ist als die aktuelle Zeit abzüglich der Pause...
    if(last_millis < (current_millis-WAIT_DELAY)) {
      //Setze Zeit des letzten Durchlaufs auf Beginn des aktuellen Durchlaufs
      last_millis = current_millis;
      Serial.print("Ausgabe nach ");
      Serial.print(current_millis);
      Serial.println("ms.");
    }
}
