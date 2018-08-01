# 05 - MQTT

[MQTT](http://mqtt.org/faq) ist ein leichtgewichtiges und sehr einfach gehaltenes Machine-zu-Maschine-Protokoll und steht für Message Queue Telemetry Transport. Es wurde für die Datenübertragung in Netzwerken mit geringer Bandbreite oder hoher Latenz entworfen. MQTT ist eine Alternative zur Datenübertragung per HTTP.

## Grundlagenwissen

MQTT basiert auf einer Topic-Struktur, ähnlich eines Webforums. Es gibt eigentlich nur 2 Operationen - ein Thema (*Topic*) abonnieren (*subscribe*) oder in ein Thema schreiben (*publish*). Wenn ein Client in ein Thema schreibt, erhalten alle Abonnenten des Themas die Nachricht. Diese Funktionalität wird in der [*PubSubClient*-Bibliothek](https://github.com/knolleary/pubsubclient) (Bitte Einschränkungen beachten!) bereitgestellt, die wir in unseren Sketch einbinden müssen.

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

Das *PubSubClient*-Objekt wird anschließend parametriert.

```
mqttClient.setServer(broker, port);
mqttClient.setCallback(callback);
```

Mittels der *setServer*-Methode werden Server-Domain und -Port an das Objekt geschrieben, per *setCallback*-Methode wird definiert welche Methode des Sketches bei Eintreffen einer neuen Nachricht aufgerufen wird.

```
void callback(char* topic, byte* payload, unsigned int msgLength) {
    Serial.print("[MQTT] Message in topic ");
    Serial.println(topic);
    Serial.println("[MQTT] Message payload: ");
    for(int i = 0; i < msgLength; i++) {
      Serial.print((char) payload[i]);
    }
    Serial.println();
}
```

Die *callback*-Methode erhält dann als Parameter das Thema aus dem die Nachricht entstammt als `char* topic`, die Nachricht selbst als Byte-Array `byte* payload` und die Länge (Anzahl der Zeichen) der Nachricht als Ganzzahl `unsigned int msgLength`. Diese können dann zu einem lesbaren Ergebnis verarbeitet werden.

Nach Verbindung zum Broker mittels

```
mqttClient.connect(clientName);
```

wobei auch der Name des Clients gesetzt wird, können die *publish*- und *subscribe*-Methoden genutzt werden.

Das Schreiben von Nachrichten in ein Thema wird Mittels

```
mqttClient.publish(topicName, "Hello from ESP8266");
```

realisiert. Das Abonnieren eines Themas Operationen

```
mqttClient.subscribe(topicName);
```


## Weiterentwicklung

MQTT besitzt mehrere sog. QoS-Level. Die verwendete Bibliothek ist allerdings beschränkt. Gibt es eine Möglichkeit andere Level umzusetzen?

## Weiterführende Literatur

* [MQTT](http://mqtt.org/faq) - Offizielle FAQ zum MQTT-Protokoll
* [PubSubClient](https://github.com/knolleary/pubsubclient) - Git der PubSubClient-Library

## Entwickelt mit

* [Atom](https://atom.io/) - Ein frei konfigurierbarer Texteditor
* [Platform.io](https://platformio.org/) - Eine Open-Source-Entwicklungsumgebung für die Entwicklung von IoT-Systemen

## Autor

* **Christian Schneider** - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

Dieses Projekt wurde unter der MIT License veröffentlicht -  [LICENSE.md](LICENSE.md) für Details
