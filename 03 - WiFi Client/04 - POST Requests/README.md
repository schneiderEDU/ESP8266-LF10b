# 04 - POST Request

Der eigentliche Unterschied zwischen GET- und POST-Requests liegt in der Gestaltung der Anfragen. Dies muss auch serverseitig berücksichtigt werden. Ein Skript nimmt meistens ausschließlich Daten per GET- oder POST-Request entgegen.

## Grundlagenwissen

Anders als der GET-Request, werden die zu übertragenden Daten beim POST-Request nicht an die URL angehangen, sondern in den Nachrichtenbody eingekapselt. Damit der Server mit den Daten umzugehen weiß, müssen wir zunächst noch einen [Header](https://wiki.selfhtml.org/wiki/HTTP/Header/Accept) zum Request hinzufügen.

```
client.addHeader("Content-Type", "application/x-www-form-urlencoded");
```

Um die Daten nun per POST- statt GET-Request zu versenden, verwenden wir die *POST*-Methode.

```
client.POST("a=3&b=4");
```

In dieser werden die Daten ähnlich des GET-Requests als Parameter übergeben.
Der eigentliche Request wird dann vom *HTTPClient* erzeugt.

```
POST /esp8266/postrequest/index.php HTTP/1.1
Host: iot.schneider-edu.it
Content-Type: application/x-www-form-urlencoded
Cache-Control: no-cache

a=3&b=4
```

Der POST-Request hat den Vorteil die Daten im Payload der Nachricht zu übertragen, womit sie nicht im Browserverlauf, den Serverlogs oder in den Lesezeichen gespeichert werden können. Dies bringt einen Zuwachs an Sicherheit. Die Zeichenrestriktion der GET-Requests entfällt ebenfalls, da der Payload theoretisch unendlich groß werden kann. Auch die Art der zu übertragenden Daten ist nicht auf ASCII-Zeichen beschränkt, sondern es können jegliche Binärdaten, wie z.B. auch Dateien, per POST-Request übertragen werden. Dabei ist der Header entsprechend anzupassen.
Die Antwort kann jedoch nicht gecached werden und bei einer erneuten Übertragung der Daten muss die komplette Anfrage erneut gesendet werden, was unter Umständen zu einer erhöhten Netz- und Serverlast führen kann.


## Weiterentwicklung



## Weiterführende Literatur

* [ASCII](https://de.wikipedia.org/wiki/American_Standard_Code_for_Information_Interchange) - Erläuterungen zu American Standard Code for Information Interchange (ASCII)
* [Binärdaten](https://de.wikipedia.org/wiki/Bin%C3%A4rdatei) - Erläuterung zu Binärdaten
* [Client](http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html) - Beispiele für die Verwendung *ESP8266HTTPClient.h*-Bibliothek
* [GET vs. POST](https://www.diffen.com/difference/GET-vs-POST-HTTP-Requests) - Vergleich von GET- und POST-HTTP-Requests
* [HTTP Anfrage-Header](https://wiki.selfhtml.org/wiki/HTTP/Header/Accept) - HTTP-Anfrageheader
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
