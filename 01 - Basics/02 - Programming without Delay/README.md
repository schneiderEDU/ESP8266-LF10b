# 02 - Programming without Delay

Möchte man eine bestimmte Aufgabe alle x Millisekunden abarbeiten, so kann man nicht mehr mit

```
delay(MS)
```
arbeiten.

## Grundlagenwissen

Ein Mikrocontroller, wie der ESP8266 oder auch Arduinos, können keine Nebenläufigkeit (Threads) verarbeiten. Es können also keine Aufgaben parallel abgearbeitet werden, denn es wird immer wieder nur die *loop*-Funktion durchlaufen. Wenn man diese jetzt mittels der *delay*-Funktion für x Millisekunden anhält, pausiert der gesamte Mikrocontroller für diese Zeit und es können keine anderen Aufgaben ausgeführt werden. Das wäre vergleichbar mit dem Stop-And-Go im Straßenverkehr. Ihr kennt das, nervig, stressig und nicht zielführend. Daher müssen wir uns nun einen neuen Weg überlegen unseren Sketch aufzubauen.

## Vorüberlegung

Wir verwenden statt der *delay*-Funktion eine konstante Ganzzahl, in der wir die Wartezeit bis zur nächsten Ausführung des Codes festlegen. Dies geschieht im Programmtext mit der konstanten globalen Variable

```
const int WAIT_DELAY = 1000;
```

In diesem Fall liegt die Wartezeit bei 1000ms (also 1 Sekunde).
Weiterhin benötigen wir eine zusätzliche Variable, in der wir die Zeit des letzten Durchlaufs speichern. Dies tun wir in der Variablen

```
long last_millis = -1;
```

Diese initialisieren wir mit dem Wert -1 für den ersten Durchlauf. In unserer *loop*-Funktion holen wir uns nun zunächst die aktuelle Ausführungszeit in Millisekunden per *millis*-Funktion und speichern diese in einer Variablen

```
long current_millis = millis();
```

Nun prüfen wir, ob die Zeit der letzten Ausführung (*last_millis*) kleiner ist als die aktuelle Zeit abzüglich der eingangs definierten konstanten Wartezeit (*WAIT_DELAY*)

```
if(last_millis < (current_millis-WAIT_DELAY)) { }
```

Falls dieser Fall wahr ist, dann soll der Programmblock innerhalb der *if*-Anweisung ausgeführt werden. Andernfalls wird der enthaltene Programmblock übersprungen und der evtl. vorhandene Programmtext nach der *if*-Anweisung ausgeführt.

Bei Ausführung des in der *if*-Anweisung enthaltenen Programmblocks wird nun als erstes die aktuelle Ausführungszeit(*current_millis*) als Zeit der letzten Ausführung (*last_millis*) gesetzt.

```
last_millis = current_millis;
```

Damit ist eine weitere korrekte Ausführung des Programms gewährleistet, da sonst der Programmblock innerhalb des *if*-Blocks ausgeführt würde, weil die Variable *last_millis* stets den Wert *-1* besitzt.

## Weiterentwicklung

Durch das Deklarieren mehrerer Wartezeiten und entsprechender *if*-Anweisungen, ist es möglich ein Scheinparallelverarbeitung zu erzeugen.

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
