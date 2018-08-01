# 01 - Basic Webserver

Der ESP8266 kann nicht nur als (HTTP-)Client dienen, sondern auch als HTTP-Server. Diese Funktionalität lässt sich u.A. dazu benutzen kleine Webseiten zu Steuerungs- oder Anzeigezwecken auszurollen.

## Grundlagenwissen

Die Library `ESP8266WebServer.h` stellt alle Funktionalitäten für die Realisierung eines Webservers auf einem ESP8266 bereit. Sie muss lediglich inkludiert werden.

```
#include <ESP8266WebServer.h>
```

Webserver laufen in der Regel auf Port 80. Dieser Port ist für das HTTP-Protokoll standardisiert (HTTPS läuft über Port 443). Wir verwenden in unserem Beispiel jedoch einen anderen Port. Diesen deklarieren wir in einer Konstanten und übergeben diese bei Erzeugung der *ESP8266WebServer*-Objekts

```
const int serverPort = 1337;
ESP8266WebServer server(serverPort);
```

Der Aufruf über den Browser lautet dann `http://*IP*:1337/`.
Nun muss zumindest für das Wurzelverzeichnis, also den minimalen Aufruf im Browser ohne Angabe von Unterverzeichnissen und Dateien gehandled werden. Die geschieht über die *on*-Methode des *ESP8266WebServer*-Objekts.

```
server.on("/", handleRootPath);
```

Der Slash symbolisiert das Wurzelverzeichnis, bei dessen Aufruf die Methode `handleRootPath` ausgeführt wird.

```
void handleRootPath() {
    server.send(200, "text/plain", "This is the root path");
}
```

Diese sendet eine Antwort mit dem HTTP-Statuscode 200 (OK), als Antworttyp normalen Text (`text/plain`) und den Text `This is the root path`.

Das Verhalten für den `/alt`-Pfad ist analog. Für den Aufruf eines anderen Pfades, der nicht explizit gehandled wurde, wird die `handleNotFound`-Methode ausgeführt. Dies wird spezifiziert mittels

```
server.onNotFound(handleNotFound);
```

Diese sendet statt dem HTTP-Statuscode 200 (OK) jedoch 404 (Not Found) und ebenfalls eine Fehlermeldung als Text.

Mittels `server.begin()` wird der Server gestartet.

Anfragen von Clients werden intern in der *handleClient*-Methode behandelt

```
server.handleClient();
```

## Weiterentwicklung



## Weiterführende Literatur

* [ESP8266WebServer Docs](https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html) - Dokumentation der ESP8266WebServer-Klasse
* [HTTP-Statuscodes](https://de.wikipedia.org/wiki/HTTP-Statuscode) - Liste der HTTP-Statuscodes
* [Liste der standardisierten Ports](https://de.wikipedia.org/wiki/Liste_der_standardisierten_Ports) - Liste der standardisierten, registrierten und dynamischen Ports

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
