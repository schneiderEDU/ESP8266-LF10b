# 02 - Manual Configuration

Sollte einmal kein DHCP-Server im Netzwerk verfügbar sein, oder muss aus anderen Gründen eine manuelle IP-Adresskonfiguration vorgenommen werden, so ist die auch beim ESP8266 möglich.

## Grundlagenwissen

IP-Adressen können nicht wie gewöhnlich in der Punkt-Notation (z.B. *192.168.1.100*) angegeben werden. Sie müssen als Objekt vom Typ *IPAddress* erzeugt werden. Die einzelnen Tupel der Adressen werden dann komma-separiert als Parameter übergeben.

```
IPAddress clientIP(192, 168, 1, 100);
```

Die Minimalkonfiguration besteht aus gewünschter IP-Adresse, Subnetzmaske und Gateway und kann optional um bis zu zwei DNS-Server erweitert werden. Im Beispiel ist die exemplarisch die Maximalkonfiguration gezeigt. Dafür sollten zunächst die nötigen Objekte vom Typ *IPAddress* erzeugt werden. Nach dem Start des Verbindungsaufbaus mittels *Wifi.begin(ssid, password)* wird nun eine weiter Zeile zur eigentlichen IP-Adresskonfiguration eingeschoben.

```
WiFi.config(clientIP, gateway, subnet, dns1, dns2);
```

Durch diesen Methodenaufruf wird die IP-Adresskonfiguration wie gewünscht vorgenommen.

## Weiterentwicklung


## Weiterführende Literatur

* [Station Class](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html) - Dokumentation der Station-Klasse der *ESP8266WiFi.h*-Bibliothek

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
