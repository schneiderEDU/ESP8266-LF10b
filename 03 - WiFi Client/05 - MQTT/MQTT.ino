#include <Arduino.h>
#include <ESP8266WiFi.h>
//Bibliothek zur Kommunikation via MQTT
#include <PubSubClient.h>

const char* ssid = "MYWIFISSID";
const char* password = "mysupersecretpassword";

const int WAIT_DELAY = 10000;
long last_millis = -1;

const char*  broker = "broker.mqtt-dashboard.com";
const int    port = 1883;
const char*  clientName = "WeMos Client";
const char*  topicName  = "hbfTest";

WiFiClient espClient;
//Erzeuge PubSubClient-Objekt
PubSubClient mqttClient(espClient);

//Callback-Methode - wird bei Erhalt einer Nachricht ausgeführt
void callback(char* topic, byte* payload, unsigned int msgLength) {
    Serial.print("[MQTT] Message in topic ");
    Serial.println(topic);
    Serial.println("[MQTT] Message payload: ");
    //Über Byte-Array iterieren und jedes Byte in Char konvertieren
    for(int i = 0; i < msgLength; i++) {
      Serial.print((char) payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected as ");
    Serial.println(WiFi.localIP());
    //Serveradresse und Port setzen
    mqttClient.setServer(broker, port);
    //Verhalten bei Callback
    mqttClient.setCallback(callback);
    //Verbindung zu Broker herstellen
    if (mqttClient.connect(clientName)) {
        Serial.print("[MQTT] Connected to ");
        Serial.print(broker);
        Serial.print(" as ");
        Serial.println(clientName);
        //Nachricht in Topic schreiben
        mqttClient.publish(topicName, "Hello from ESP8266");
        Serial.print("[MQTT] Send to topic");
        Serial.print(topicName);
        Serial.print(" message: ");
        Serial.println(message);
        //Topic abonnieren
        mqttClient.subscribe(topicName);
        Serial.print("[MQTT] Subscribed to topic ");
        Serial.println(topicName);
    }
    else {
      Serial.print("[MQTT] Connection failed with state ");
      //Informationen im Fehlerfall
      Serial.println(mqttClient.state());
    }
}

void loop() {
  //MQTT-Client kontinuierlich ausführen
  mqttClient.loop();
  long current_millis = millis();
  if(last_millis < (current_millis-WAIT_DELAY)) {
    last_millis = current_millis;

  }
}
