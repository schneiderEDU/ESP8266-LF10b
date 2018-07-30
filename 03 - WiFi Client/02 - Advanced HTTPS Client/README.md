# 02 - Advanced HTTPS Client

Wie unter [01 - Basic HTTPS Client](https://github.com/schneiderEDU/ESP8266-LF10b/tree/master/03%20-%20WiFi%20Client/01%20-%20Basic%20HTTPS%20Client) dargelegt, sind GET- und POST-Requests eine gängige Technik zur Datenübermittlung in verteilten Systemen.

## Grundlagenwissen

In diesem Beispiel wird die Bibliothek `ESP8266HTTPClient.h` nicht verwendet. Stattdessen arbeiten wir mit einem *WiFiClient*-Objekt der Bibliothek `ESP8266WiFi.h`. Dazu müssen wir nicht direkt das Ziel auf dem Server angeben, sondern den Zielserver selbst (Domain) und den Pfad zum Dokument auf dem Zielserver. Dies tun wir mittels

```
const char* domain = "iot.schneider-edu.it";
const String doc = "/esp8266/httpsclient/test.html"
```

Zusätzlich zum Fingerprint geben wir noch den HTTPS-Port an. Dieser ist standardmäßig 443.

```
const int httpsPort = 443;
```

Statt einem *HTTPClient*-Objekt erzeugen wir diesmal ein Objekt vom Typ `WiFiClientSecure`.

```
WiFiClientSecure client;
```

Der Name impliziert bereits die Verschlüsselung der Verbindung via [SSL/TLS](https://www.marcobeierer.de/wissen/ssl-tls-und-https-erklaert).
Nun wird die Verbindung zum Server mittels Domain und Port aufgebaut.

```
client.connect(domain, httpsPort);
```

Der Rückgabewert der Funktion ist ein boolescher Wert. Da es sich um eine gesicherte Verbindung handelt, muss die Integrität des Servers mittels des Fingerprints geprüft werden. Dies geschieht mittels

```
client.verify(fingerprint, domain);
```

Auch hier ist der Rückgabewert ein boolescher Wert. Im Gegensatz zum `HTTPClient` muss in diesem Fall der eigentliche HTTP-Request manuell zusammengebaut und an den Server gesendet werden.

```
client.print(String("GET ") + doc + " HTTP/1.1\r\n" +
     "Host: " + domain + "\r\n" +
     "User-Agent: AdvancedHTTPSClientOnESP8266\r\n" +
     "Connection: close\r\n\r\n");
```

Die Antwort des Servers muss ebenso manuell ausgewertet werden.

```
while (client.connected()) {
  String line = client.readStringUntil('\n');
  if(line == "\r") {
    Serial.println("[Response] receiving headers DONE!");
  }
  Serial.print("[Response] ");
  Serial.println(line);
}
Serial.println("[HTTPS] Closing connection... successful");
delay(1000);
```
Zunächst werden die Header (Metadaten) übertragen. Dieser Block wird zeilenweise übertragen und mittels [Escapesequenz](https://de.wikipedia.org/wiki/Escape-Sequenz#In_C_und_verwandten_Programmiersprachen) `\r` beendet. Ein Zeilenumbruch wird als `\n` dargestellt.
Anschließend werden die Nutzdaten (Payload), ebenfalls zeilenweise, übertragen.
Im Header des Requests wurde bereits festgelegt die Verbindung automatisch nach Übertragung der Antwort zu schließen, weshalb dies nicht mehr explizit geschehen muss. Mittels *delay* wird dem Server Zeit eingeräumt die Antwort zu übertragen, bevor eine neue Anfrage vom ESP8266 gesendet werden kann.

Dies scheint im ersten Moment komplizierter, allerdings lässt dies dem Programmierer mehr Freiheiten in der Gestaltung der Kommunikation. Es gibt jedoch kein "besser" oder "schlechter" zwischen  `WiFiClientSecure` und `HTTPClient`.  Auf dem gegenwärtigen Niveau der zu realisierenden Programme ist die Auswahl der Bibliothek Geschmacksache.



## Weiterentwicklung

Der GET-Request wurde ohne Parameter ausgeführt. Dies dient lediglich dazu ein Dokument von einem Server zu holen. Jedoch ist die Technik hauptsächlich zur Datenverarbeitung und -übermittlung gedacht. Können wir das Beispiel um Daten erweitern und den Request so für uns generell nutzbar machen?

## Weiterführende Literatur

* [Client](http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html) - Beispiele für die Verwendung *ESP8266HTTPClient.h*-Bibliothek
* [Escapesequenz](https://de.wikipedia.org/wiki/Escape-Sequenz#In_C_und_verwandten_Programmiersprachen) - Escapesequenzen in C
* [HTTP Protokoll](https://www.elektronik-kompendium.de/sites/net/0902231.htm) - Erläuterungen zum HTTP-Protokoll
* [HTTPS](https://www.marcobeierer.de/wissen/ssl-tls-und-https-erklaert) - Erläuterun zu HTTPS, SSL und TLS
* [WebHooks](https://de.wikipedia.org/wiki/WebHooks) - Kurze Erläuterung und Liste mit Anwendern von WebHooks

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
