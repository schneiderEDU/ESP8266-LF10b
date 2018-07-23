# 05 - Scanning

Manchmal ist es notwendig, v.a. zu Diagnosezwecken, nach allen Drahtlosnetzwerken zu scannen, um Informationen über diese zu erhalten, wie z.B. den verwendeten Kanal oder die Signalstärke.

## Grundlagenwissen

Das *WiFi*-Objekt besitzt neben seinen Methoden zur Konnektivität auch Methoden um nach Drahtlosnetzwerken zu suchen und Informationen über diese zu liefern. Um dies zu ermöglichen, versetzen wir den ESP8266 in den Station-Modus mittels

```
WiFi.mode(WIFI_STA);
```

und trennen alle aktiven Verbindungen mittels

```
WiFi.disconnect();
```

Das *WiFi*-Objekt stellt mit `scanNetworksAsync(onComplete, hidden)` eine Funktion zum asynchronen Scan nach Drahtlosnetzwerken bereit. `onComplete` wird nach erfolgtem Scan ausgeführt, während `hidden` einen Wahrheitswert (`true` oder `false`) annehmen muss, um entweder Drahtlosnetzwerke mit versteckten SSIDs in den Scan mit einzubeziehen, oder eben nicht. Mit dem Aufruf

```
WiFi.scanNetworksAsync(showFoundNetworks, true);
```

wird ein Scan, inkl. Drahtlosnetzwerken mit versteckter SSID, und nach Abschluss die Funktion `showFoundNetworks()` ausgeführt.

Diese Funktion erhält eine Ganzzahl (in diesem Fall `numNetworks`) als Parameter, die die Anzahl gefundener Drahtlosnetzwerke repräsentiert.
Mittels *for*-Schleife wird nun über die Ergebnismenge des Scans iteriert. Für jedes gefundene Drahtlosnetzwerk können nun verschiedene Informationen ausgelesen werden. Diese sind der folgenden Tabelle zu entnehmen.

| Funktion | Rückgabewert |
| :--------- | :-------------|
| `WiFi.SSID()` | liefert die SSID eines nicht versteckten Drahtlosnetzwerks|
| `WiFi.channel()` | liefert den verwendeten Kanal des Drahtlosnetzwerks |
| `WiFi.RSSI()` | liefert die Signalstärke (*Received Signal Strength Indication*) des Drahtlosnetzwerks in dBm |
| `WiFi.encryptionType()` | liefert den Verschlüsselungstyp des Drahtlosnetzwerks |
| `WiFi.isHidden()` | liefert die Sichtbarkeit des Drahtlosnetzwerks |




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
