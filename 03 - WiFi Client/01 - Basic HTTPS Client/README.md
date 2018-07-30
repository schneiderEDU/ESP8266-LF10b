# 01 - Basic HTTPS Client

Gerade im Internet der Dinge wird die Inter-Systemkommunikation oftmals über [Webhooks](https://de.wikipedia.org/wiki/WebHooks) realisiert. Dabei spielen GET- und noch viel mehr POST-Requests eine Rolle. Sie dienen dem Abfragen und Übermitteln von Daten von und zu einem Server. Der ESP8266 ist ebenfalls in der Lage diese Technik zu unterstützen.

## Grundlagenwissen

Zur Verwendung dieser Funktionalität benötigen wir einen *HTTPClient*, der eine Verbindung zu einem Server über das HTTP(S)-Protokoll aufbauen kann. Dieser wird durch die Bibliothek `ESP8266HTTPClient.h` bereitgestellt. Diese ist zu inkludieren, per

```
#include <ESP8266HTTPClient.>
```

Darüberhinaus wird ein Verbindungsziel in Form einer URL benötigt. Dieses legen wir in einer Variablen fest.

```
const char* url = "https://iot.schneider-edu.it/esp8266/httpsclient/test.html";
```

Ebenso, was schon an der URL zu erkennen ist, handelt es sich um eine verschlüsselte [HTTPS](https://www.marcobeierer.de/wissen/ssl-tls-und-https-erklaert)-Verbindung handelt und der Server diese auch erzwingt, benötigen wir den Fingerprint des Serverzertifikats. Diesen legen wir ebenfalls in einer Variablen ab.

```
const char* fingerprint = "e992449775c128d1d15f3e13ad81e9951e58ce65";
```

Um den HTTP(S)-Client verwenden zu können, muss zunächst ein Objekt der *ESP8266HTTPClient*-Klasse instanziiert werden. Dies geschieht mit

```
HTTPClient client;
```

Über das *client*-Objekt kann nun die, in unserem Fall verschlüsselte, Verbindung zum Zielserver aufgebaut werden. Dazu werden Zielserver und Fingerprint des Serverzertifikats des Zielservers als Parameter an die *begin*-Methode übergeben.

```
client.begin(url, fingerprint);
```

Per `GET` wird nun versucht das Dokument vom Server zu holen. Als Rückgabewert erhält man einen HTTP-Statuscode, den man auswerten kann. Falls dieser größer 0 ist, gabe es keine Probleme mit der Verbindung selbst. Bei Erfolg erhalten wir den Statuscode 200, welcher als `HTTP_CODE_OK` in einer Konstanten in der Bibliothek hinterlegt ist.
In diesem Fall können wir uns mittels *getString*-Methode die Nutzdaten des Dokuments liefern lassen.

```
client.getString();
```

Nach kompletter Abwicklung des Requests, gilt es die Verbindung "sauber" zu trennen. Dies geschieht mittels

```
client.end();
```

Damit wird das instanziierte *client*-Objekt ebenfalls zerstört und der von diesem allokierte Speicherbereich wieder zur Verwendung freigegeben.

## Weiterentwicklung

Der GET-Request wurde ohne Parameter ausgeführt. Dies dient lediglich dazu ein Dokument von einem Server zu holen. Jedoch ist die Technik hauptsächlich zur Datenverarbeitung und -übermittlung gedacht. Können wir das Beispiel um Daten erweitern und den Request so für uns generell nutzbar machen?

## Weiterführende Literatur

* [Client](http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html) - Beispiele für die Verwendung *ESP8266HTTPClient.h*-Bibliothek
* [HTTP Protokoll](https://www.elektronik-kompendium.de/sites/net/0902231.htm) - Erläuterungen zum HTTP-Protokoll
* [HTTPS](https://www.marcobeierer.de/wissen/ssl-tls-und-https-erklaert) - Erläuterungen zu HTTPS, SSL und TLS
* [WebHooks](https://de.wikipedia.org/wiki/WebHooks) - Kurze Erläuterung und Liste mit Anwendern von WebHooks

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
