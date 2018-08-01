# 05 - MQTT

[MQTT](http://mqtt.org/faq) ist ein leichtgewichtiges und sehr einfach gehaltenes Machine-zu-Maschine-Protokoll und steht für Message Queue Telemetry Transport. Es wurde für die Datenübertragung in Netzwerken mit geringer Bandbreite oder hoher Latenz entworfen. MQTT ist eine Alternative zur Datenübertragung per HTTP.

## Grundlagenwissen

MQTT basiert auf einer Topic-Struktur, ähnlich eines Webforums. Es gibt eigentlich nur 2 Operationen - ein Thema (*Topic*) abonnieren (*subscribe*) oder in ein Thema schreiben (*publish*). Wenn ein Client in ein Thema schreibt, erhalten alle Abonnenten des Themas die Nachricht. Diese Funktionalität wird in der *PubSubClient*-Bibliothek bereitgestellt, die wir in unseren Sketch einbinden müssen.

```
#include <PubSubClient.h>
```

Zur Realisierung der Kommunikation bedarf es eines Serverdienstes, der diese steuert - dem sog. *Broker*. Diesen kann man selbst in einem Netzwerk betreiben, oder einen öffentlichen Broker benutzen. Wir nutzen in diesem Beispiel einen öffentlichen Broker, für den wir die Verbindungsdaten festlegen müssen.

```
const char*  broker = "broker.mqtt-dashboard.com";
const int    port = 1883;
const char*  clientName = "WeMos Client";
const char*  topicName  = "hbfTest";
```

Neben der Domain des Brokers `broker.mqtt-dashboard.com` und dem Port `1883` (`8883` für verschlüsselte Kommunikation), legen wir auch den Namen unseres Clients `WeMos Client` und das Thema `hbfTest` fest. Anschließend erzeugen wir ein Objekt des bereits bekannten `WiFiClient` und eines der Klasse `PubSubClient`.

```
WiFiClient espClient;
PubSubClient mqttClient(espClient);
```

Wir übergeben das *WiFiClient*-Objekt per Parameter an das *PubSubClient*-Objekt, da dieses auf dem *WiFiClient*-Objekt aufsetzt.

## Weiterentwicklung

[in Bearbeitung]

## Weiterführende Literatur

* [MQTT](http://mqtt.org/faq) - Offizielle FAQ zum MQTT-Protokoll

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
