# 03 - GET Request

Der eigentliche Unterschied zwischen GET- und POST-Requests liegt in der Gestaltung der Anfragen. Dies muss auch serverseitig berücksichtigt werden. Ein Skript nimmt meistens ausschließlich Daten per GET- oder POST-Request entgegen.

## Grundlagenwissen

Ein GET-Request ist die für den Menschen einfacher zu betrachtende Form einer Anfrage. Die zu übertragenden Werte werden einfach an die URL, getrennt durch ein `?` angehangen, gefolgt von Variablennamen mit Wertezuweisungen per `=`. Zur Übertragung mehrerer Werte können diese per `&` miteinander verbunden werden. Im Beispiel sieht der Request dann wie folgt aus:

```
https://iot.schneider-edu.it/esp8266/getrequest/index.php?a=3&b=4
```

D.h. es werden folgende Werte übertragen:

```
a = 3
b = 4
```

Der Rest des Beispiels ist identisch mit [01 - Basic HTTPS Client](https://github.com/schneiderEDU/ESP8266-LF10b/tree/master/03%20-%20WiFi%20Client/01%20-%20Basic%20HTTPS%20Client).

GET-Requests sind einfach zu konstruieren und können, sofern sie per Browser ausgelöst werden sollen, auch als Lesezeichen gespeichert werden. Weiterhin ist es möglich die Daten zu cachen. Allerdings sind damit auch die Daten direkt in der URL, in den Serverlogs und ggf. im Browserverlauf sichtbar. Dies ist vor allem ein Problem wenn sicherheitskritische Daten übertragen werden. Weiterhin sind GET-Requests durch die maximale Länge einer URL von 2048 Zeichen begrenzt. Diese Zeichen dürfen auch nur ASCII-Zeichen sein.

## Weiterentwicklung



## Weiterführende Literatur

* [Client](http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html) - Beispiele für die Verwendung *ESP8266HTTPClient.h*-Bibliothek
* [GET vs. POST](https://www.diffen.com/difference/GET-vs-POST-HTTP-Requests) - Vergleich von GET- und POST-HTTP-Requests
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
