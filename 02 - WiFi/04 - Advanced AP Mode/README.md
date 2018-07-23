# 04 - Advanced AP Mode

Der ESP8266 kann nicht nur zu einem vorhandenen Drahtlosnetzwerk verbinden, sondern auch ein eigenes Drahtlosnetzwerk ("Hotspot" sagt man wohl heute) aufspannen.

## Grundlagenwissen

Neben der Minimalkonfiguration kann auch eine eigene IP-Konfiguration und eine erweiterte Konfiguration des AP-Parameter vorgenommen werden. Mittels

```
WiFi.softAPConfig(localIP, gateway, netmask);
```

kann die IP-Adresskonfiguration des Access Points, analog zur manuellen Konfiguration im Station-Modus [02 - Manual Configuration](https://github.com/schneiderEDU/ESP8266-LF10b/tree/master/02%20-%20WiFi/02%20-%20Manual%20Configuration) vorgenommen werden.
Die *softAP*-Methode kann noch um die optionalen Parameter `channel` und `hidden` erweitert werden.

```
WiFi.softAP(ssid, password, channel, hidden);
```

Dabei definiert `channel` den zu verwendenden Kanal des Access Points (zwischen 1 und 13, Standard 1). Der Parameter `hidden` dient die SSID des Drahtlosnetzwerks zu verstecken. Dieser muss dazu auf `true` gesetzt werden.


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
