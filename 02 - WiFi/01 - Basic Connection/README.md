# 01 - Basic Connection

Der größte Vorteil des ESP8266 ist seine WLAN-Konnektivität. Eine Verbindung zu einem vorhandenen Drahtlosnetzwerk ist mit wenig Programmcode realisiert.

## Grundlagenwissen

Eine grundlegende Verbindung zu einem vorhandenen Drahtlosnetzwerk, welches über einen DHCP-Dienst zur dynamischen Verteilung von IP-Adressen verfügt.
Alle grundlegenden Drahtlosfunktionen sind in der Bibliothek *ESP8266WiFi.h* enthalten, die im Kopf der Datei eingebunden werden muss. Die geschieht über

```
#include <ESP8266WiFi.h>
```

Zur Wahrung der Übersichtlichkeit des Programmtextes, bietet es sich an die Zugangsdaten des WLANs in Konstanten zu hinterlegen.

```
const char* ssid = "MYWIFISSID";
const char* password = mysupersecretpassword";
```

Für die eigentliche Verbindung ist lediglich ein Aufruf der *begin*-Funktion des *WiFi*-Objekts mit Übergabe der Zugangsdaten nötig.

```
WiFi.begin(ssid, password);
```

Nun kann per Schleife die weitere Ausführung des Sketches aufgehalten werden, bis die Verbindung aufgebaut wurde. In diesem speziellen Fall wird einmal pro Sekunde überprüft, ob eine Verbindung aufgebaut wurde. Ist dies der Fall, so wird mit der Programmausführung fortgefahren.

```
while(WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
}
```

Die *status*-Methode des *WiFi*-Objekts kann verschiedene Rückgabewerte haben. Bei erfolgreicher Verbindung wird von der *status*-Methode *WL_CONNECTED* zurückgegeben.

###Wichtige Rückgabewerte von WiFi.status()

| Rückgabewert  | Bedeutung |
| :------------ | :-------- |
| WL_CONNECTED | Es besteht eine Verbindung zum Drahtlosnetzwerk. |
| WL_CONNECT_FAILED | Es konnt keine Verbindung zum Drahtlosnetzwerk aufgebaut werden. |
| WL_CONNECTION_LOST | Die Verbindung zum Drahtlosnetzwerk ging verloren. |
| WL_DISCONNECTED | Die Verbindung zum Drahtlosnetzwerk wurde abgebaut.




## Weiterentwicklung



## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
