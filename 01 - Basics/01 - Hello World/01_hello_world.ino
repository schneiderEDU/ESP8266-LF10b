//Globale Variable
int i = 1;

//setup() wird zum Start des SoCs genau einmal ausgeführt
void setup () {
  //Initialisiere serielle Schnittstelle auf 115200 Baud
  Serial.begin(115200);
  Serial.println("Setup");
}

//loop() wird bis zum Spannungsverlust des SoCs zyklisch durchlaufen
void loop () {
  Serial.print (i);
  Serial.println(". Loop\n");
  i++;
  //Warte 1000ms
  delay(1000);
}
