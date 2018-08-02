# 01 - I2C Bus Scanner

## Projektauftrag

Deine Firma erhält eine Vielzahl an verschiedenen Sensoren und Aktoren, die den I2C-Bus zur Kommunikation verwenden. Leider weiß niemand über welche Adresse die Sensoren und Aktoren anzusprechen sind. Die Dokumentationen der Bauteile wurden nicht mitgeliefert und lassen sich auch nicht auf der Seite des Herstellers finden. Es gibt lediglich den Hinweis, dass die Geräte eine 7 Bit große Adresse besitzen. Sie wurden beauftragt eine Lösung für dieses Problem zu entwickeln.

## Nötiges Fachwissen

### I2C

Das I2C-Protokoll (auch *IIC*, Inter-integrated curcuit) wurde für die Kommunikation von mehreren Sensoren oder Aktoren (*"slaves"*) mit einem oder mehreren Steuergeräten (*"master"*) über einen Bus entworfen. Ähnlich wie auch andere Bussysteme ist I2C zur Verwendung über kurze Entfernungen, innerhalb eines Geräts, ausgelegt. Zur Kommunikation werden zwei Signalleitungen benötigt, jeweils eine für ein Taktsignal (*SCL*) und die Daten (*SDA*). Jedes Gerät, besser jeder IC, erhält seitens des Herstellers laut ursprünglicher Spezifizierung eine 7 Bit große Adresse, wodurch es theoretisch möglich ist Geräte mit Adressen von 0 bis 127 zu adressieren. In einer späteren Spezifizierung wurde die Adressgröße um 3 Bit erweitert, wodurch sich auch der Adressraum auf 0 bis 1023 ausweitet.

### ESP8266
Der ESP8266 unterstützt das I2C-Protokoll. Der WeMos D1 mini im Speziellen stellt die I2C-Funktionalität an den Pins D1 (*SCL*) und D2 (*SDA*) bereit.

## Vorüberlegungen

## Durchführung

[in Bearbeitung]

## Fazit


## Literatur

* [I2C](https://learn.sparkfun.com/tutorials/i2c) - Sparkfun Tutorial zu I2C
* [Pinout D1 mini](https://steve.fi/Hardware/d1-pins/) - Pinout für den WeMos D1 mini

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Verwendete Bibliotheken

* [Wire](https://www.arduino.cc/en/Reference/Wire) - Wire Library zur Kommunikation mit I2C-Geräten

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
