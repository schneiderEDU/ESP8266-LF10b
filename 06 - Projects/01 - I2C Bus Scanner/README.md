# 01 - I2C Bus Scanner

## Projektauftrag

Deine Firma erhält eine Vielzahl an verschiedenen Sensoren und Aktoren, die den I2C-Bus zur Kommunikation verwenden. Leider weiß niemand über welche Adresse die Sensoren und Aktoren anzusprechen sind. Die Dokumentationen der Bauteile wurden nicht mitgeliefert und lassen sich auch nicht auf der Seite des Herstellers finden. Sie wurden beauftragt eine Lösung für dieses Problem zu entwickeln.

## Vorüberlegungen und Fachwissen

### I2C

Das I2C-Protokoll (auch *IIC*, Inter-integrated curcuit) wurde für die Kommunikation von mehreren Sensoren oder Aktoren (*"slaves"*) mit einem oder mehreren Steuergeräten (*"master"*) über einen Bus entworfen. Ähnlich wie auch andere Bussysteme ist I2C zur Verwendung über kurze Entfernungen, innerhalb eines Geräts, ausgelegt. Zur Kommunikation werden zwei Signalleitungen benötigt, jeweils eine für ein Taktsignal (*SCL*) und die Daten (*SDA*). Die Datenrate des I2C-Busses variiert zwischen
- 100 kHz
- 400 kHz (*fast-mode*)
-   1 MHz (*fast-mode plus*)
- 3,4 MHz (*high-speed mode*)
-   5 MHz (*ultra-fast mode*)

Jedes Gerät


## Durchführung

[in Bearbeitung]

## Fazit


## Literatur

* [I2C](https://learn.sparkfun.com/tutorials/i2c) - Sparkfun Tutorial zu I2C

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Verwendete Bibliotheken

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
