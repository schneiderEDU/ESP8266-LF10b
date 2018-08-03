# 03 - Webserver using SPIFFS

Den HTML-Code im Sketch zu erzeugen führt unter Umständen dazu, dass der Sketch unübersichtlich wird. Die Trennung von Programm und "Nutzdaten" macht in einigen Fällen durchaus Sinn. Der ESP8266 besitzt für diese Fälle einen [Flashspeicher](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html), auf dem Konfigurationsdateien, andere Sketches oder auch Daten für einen Webserver abgelegt werden können.

## Grundlagenwissen

Dieses Beispiel adaptiert das Beispiel [01 - Basic Webserver](https://github.com/schneiderEDU/ESP8266-LF10b/tree/master/04%20-%20WiFi%20Server/01%20-%20Basic%20Webserver) und erweitert dieses insofern, dass der HTML-Code der Indexseite als `index.html` im Flashspeicher des ESP8266 abgelegt werden. Hierfür wird die Bibliothek `FS.h` (und in Teilen `detail\RequestHandlersImpl.h`), benötigt. Diese werden inkludiert.

```
#include <FS.h>
#include <detail\RequestHandlersImpl.h>
```

Mittels

```
SPIFFS.begin();
```

wird das Dateisystem eingehangen, ähnlich den Dateisystemen unter Linux-Betriebssystemen. Das *ESP8266WebServer*-Objekt verfügt über die Methode `serveStatic()`, die es ermöglicht statischen Inhalt aus dem Flash-Dateisystem einzuhängen.

```
server.serveStatic("/", SPIFFS, "/index.html");
```

Bei Aufruf des Wurzelverzeichnisses des Webservers (`"/"`) wird die Datei `index.html` aus dem Flash-Dateisystem (`SPIFFS`) ausgeliefert.

Der Rest des Sketches ist analog zum vorgenannten Beispiel.


## Weiterentwicklung


## Weiterführende Literatur

* [ESP8266WebServer Docs](https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html) - Dokumentation der ESP8266WebServer-Klasse
* [FS](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html) - Erläuterung zum Flash Layout
* [HTTP-Statuscodes](https://de.wikipedia.org/wiki/HTTP-Statuscode) - Liste der HTTP-Statuscodes
* [Liste der standardisierten Ports](https://de.wikipedia.org/wiki/Liste_der_standardisierten_Ports) - Liste der standardisierten, registrierten und dynamischen Ports
## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
