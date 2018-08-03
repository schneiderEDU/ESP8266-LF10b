# 01 - I2C Bus Scanner

## Projektauftrag

Deine Firma erhält eine Vielzahl an verschiedenen Sensoren und Aktoren, die den I2C-Bus zur Kommunikation verwenden. Leider weiß niemand über welche Adresse die Sensoren und Aktoren anzusprechen sind. Die Dokumentationen der Bauteile wurden nicht mitgeliefert und lassen sich auch nicht auf der Seite des Herstellers finden. Es gibt lediglich den Hinweis, dass die Geräte eine 7 Bit große Adresse besitzen. Sie wurden beauftragt eine Lösung für dieses Problem zu entwickeln.

## Nötiges Fachwissen

### I2C

Das I2C-Protokoll (auch *IIC*, Inter-integrated circuit) wurde für die Kommunikation von mehreren Sensoren oder Aktoren (*"slaves"*) mit einem oder mehreren Steuergeräten (*"master"*) über einen Bus entworfen. Ähnlich wie auch andere Bussysteme ist I2C zur Verwendung über kurze Entfernungen, innerhalb eines Geräts, ausgelegt. Zur Kommunikation werden zwei Signalleitungen benötigt, jeweils eine für ein Taktsignal (*SCL*) und die Daten (*SDA*). Jedes Gerät, besser jeder IC, erhält seitens des Herstellers laut ursprünglicher Spezifizierung eine 7 Bit große Adresse, wodurch es theoretisch möglich ist Geräte mit Adressen von 0 bis 127 zu adressieren. In einer späteren Spezifizierung wurde die Adressgröße um 3 Bit erweitert, wodurch sich auch der Adressraum auf 0 bis 1023 ausweitet.

### ESP8266
Der ESP8266 unterstützt das I2C-Protokoll. Der WeMos D1 mini im Speziellen stellt die I2C-Funktionalität an den Pins D1 (*SCL*) und D2 (*SDA*) bereit.

## Vorüberlegungen
Um zu erkennen welche Busadressen durch ein oder mehrere Geräte belegt sind, muss jede Adresse einmal angesprochen werden. Falls man eine Antwort erhält ist ein Gerät mit dieser Adresse am Bus angeschlossen. Zur Anzeige kann das vorhandene Display nicht verwendet werden, da es selbst über I2C betrieben wird. Zwar könnte dieses Gerät aus den Scan-Ergebnissen herausgefiltert werden, aber dann wäre es nicht mehr möglich nach genau diesem Geräte-Typ zu scannen. Deshalb muss eine andere Form der Darstellung gewählt werden. Hier bietet sich eine simple Webseite an, da somit von jedem Rechner oder Smartphone im Netzwerk auf das Gerät zugegriffen werden kann und keine weitere Software, mit Ausnahme eines Browser, benötigt wird.

## Durchführung

### Realisierung des I2C-Scanners
Der I2C-Scanner wurde mittels der *Wire*-Bibliothek realisiert. Damit übernimmt der ESP8266 die Rolle des Busmasters und fragt sendet ein Paket an eine zu spezifizierende Adresse des Busses.

```
int checkAddress(int& address) {
  byte errorCode, busAddress;
  int deviceFound = 0;
  busAddress = (byte) address;
  Wire.beginTransmission(busAddress);
  errorCode = Wire.endTransmission();
  if(errorCode == 0) {
    deviceFound = 1;
  }
  else if (errorCode == 4) {
    deviceFound = 2;
  }
  return deviceFound;
}
```
Mittels `Wire.beginTransmission(busAddress)` wird eine Übertragung zum vermeintlichen I2C-Slave initiiert. Die Übertragung enthält keine Nutzdaten und wird direkt mit `Wire.endTransmission()` beendet. Diese Funktion hat verschiedene Rückgabewerte als Ganzzahlen. Der Wert `0` symbolisiert eine erfolgreiche Übertragung, während der Wert `4` einen unbekannten Fehler während der Übertragung anzeigt (Hier liegt die Vermutung nahe, dass es sich dabei um ein defektes I2C-Device handeln könnte). Alle anderen Rückgabewerte sind für unseren Fall irrelevant und können daher ausgelassen werden.

Die obige Funktion wird nun dazu verwendet um mittels einer weiteren Funktion alle Adressen von 0 bis 126 zu durchlaufen. Diese Funktion wertet gleichzeitig auch die Ergebnisse des Scans aus und generiert aus diesen den HTML-Code der späteren Webseite zur Anzeige der Scan-Ergebnisse.

```
String searchDevices() {
  int countDevices = 0;
  int countErrors = 0;
  deviceString = "<html><body><head><title>I2C Scanner</title></head><h1>I2C Scanner</h1><p><h3>Wiring</h3>SDA: "+ String(SDA) +"<br/>SCL: "+ String(SCL) + " </p><p><h3>Scan results</h3><ul>";
  for (int i = 0; i < 127; i++) {
    if(checkAddress(i) != 0) {
      if(checkAddress(i) == 1) {
        deviceString = deviceString + "<li>I2C device found ";
        countDevices++;
      }
      else {
        deviceString = deviceString + "<li>Unknown error ";
        countErrors++;
      }
      deviceString = deviceString + "at address 0x" + decToHex(i)  + "</li>";
    }
  }
  deviceString += "</ul></p>";
  deviceString += "<p>Scan completed. " + String(countDevices) + " device";
  if (countDevices != 1) deviceString += "s";
  deviceString += " found. " + String(countErrors) + " error";
  if (countErrors != 1) deviceString += "s";
  deviceString += " occured.</p><button onClick=\"window.location.reload()\">Scan again</button></body><html>";
  return deviceString;
}
```

Da die Adressen in Dezimalrepräsentation vorliegen, aber in Hexadezimalrepräsentation ausgegeben werden sollen, musste noch eine Funktion zur Konvertierung implementiert werden. Dies geschah nach dem Umrechnungsverfahren mit dem Modulo-Operator.

```
String decToHex(int decValue) {
  String hexValue;
  bool lowerSixteen = false;
  if(decValue < 16) lowerSixteen = true;
  while(decValue > 0) {
    int mod = decValue%16;
    if(mod < 10) {
      hexValue = String(mod) + hexValue;
    }
    else if (mod == 10) {
      hexValue = "a" + hexValue;
    }
    else if (mod == 11) {
      hexValue = "b" + hexValue;
    }
    else if (mod == 12) {
      hexValue = "c" + hexValue;
    }
    else if (mod == 13) {
      hexValue = "d" + hexValue;
    }
    else if (mod == 14) {
      hexValue = "e" + hexValue;
    }
    else if (mod == 15) {
      hexValue = "f" + hexValue;
    }
    decValue /= 16;
  }
  if (lowerSixteen) hexValue = "0" + hexValue;
  return hexValue;
}
```

### Implementierung des Webservers und der Webseite

Der HTML-Code wird dann mittels eigenem Webserver auf dem ESP8266 als Webseite verfügbar gemacht. Dazu wird die *ESP8266WiFiServer*-Library verwendet. Der Webserver läuft auf Port 80, dem Standard-HTTP-Port, sodass die Webseite ohne Angabe eines Ports aufgerufen werden kann. Bei Aufruf der Webseite wird die Funktion `searchDevices()` ausgeführt, die dann einen erneuten Scan des Busses durchführt und das HTML der Seite aktualisiert. Per Buttonklick wird die Seite neu geladen und damit ein neuer Suchvorgang angestoßen.

## Fazit

Hier könnten neue Erkenntnisse oder Probleme (und deren Lösung) aufgeführt und diskutiert werden.

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
