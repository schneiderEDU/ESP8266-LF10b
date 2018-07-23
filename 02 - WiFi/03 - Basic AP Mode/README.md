# 03 - Basic AP Mode

Der ESP8266 kann nicht nur zu einem vorhandenen Drahtlosnetzwerk verbinden, sondern auch ein eigenes Drahtlosnetzwerk ("Hotspot" sagt man wohl heute) aufspannen.

## Grundlagenwissen

Nahezu jeder WLAN-Adapter kann in einem Access Point-Modus versetzt werden, in dem er dann als Drahtloszugriffspunkt agiert. D.h. andere Geräte können über diesen Zugriffspunkt drahtlos miteinander vernetzt werden. Dies ist auch mit dem ESP8266 möglich. Dafür benötigt man lediglich eine SSID, der Anzeigename des Drahtlosnetzwerks, und (optional) ein Passwort, was wir aber allein aus Sicherheitsgründen nicht als optional ansehen sollten. Diese werden, genau wie schon im Station-Modus, deklariert.

```
const char* ssid = "MyOwnAP";
const char* password = "mysupersecretpassword";
```

Mittels *softAP*-Methode des *WiFi*-Objekts wird der Access Point realisiert.

```
WiFi.softAP(ssid, password);
```

Diese Methode gibt `true` (bei erfolgreicher Ausführung) bzw. `false` zurück. Damit lässt sie sich auch zu grundlegender Kontrolle der Ausführung verwenden.

Die IP-Adresse des Access Points kann mittels

```
WiFi.softAPIP();
```

ermittelt werden. Diese lautet standardmäßig `192.168.4.1`.

Um die Anzahl der verbundenen Clients zu ermitteln, ist die Methode

```
WiFi.softAPgetStationNum();
```

implementiert. Diese gibt diese Anzahl als Ganzzahl zurück.

## Weiterentwicklung


## Weiterführende Literatur

* [Soft Access Point Class](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html) - Dokumentation der SoftAP-Klasse der *ESP8266WiFi.h*-Bibliothek

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
