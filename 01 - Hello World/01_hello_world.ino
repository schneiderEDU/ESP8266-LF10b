int i = 1;

void setup () {
  Serial.begin(9600);
  Serial.println("Setup");
}
void loop () {
  Serial.print (i)
  Serial.println(". Loop");
  i++;
  delay(1000);
}
