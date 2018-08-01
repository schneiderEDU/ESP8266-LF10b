#include <Arduino.h>
#include <ESP8266WiFi.h>
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
PubSubClient mqttClient(espClient);

void callback(char* topic, byte* payload, unsigned int msgLength) {
    Serial.print("[MQTT] Message in topic ");
    Serial.println(topic);
    Serial.println("[MQTT] Message payload: ");
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
    mqttClient.setServer(broker, port);
    mqttClient.setCallback(callback);
    if (mqttClient.connect(clientName)) {
        Serial.print("[MQTT] Connected to ");
        Serial.print(broker);
        Serial.print(" as ");
        Serial.println(clientName);
        char* message = "Hello from ESP8266";
        mqttClient.publish(topicName, message);
        Serial.print("[MQTT] Send to topic");
        Serial.print(topicName);
        Serial.print(" message: ");
        Serial.println(message);
        mqttClient.subscribe(topicName);
        Serial.print("[MQTT] Subscribed to topic ");
        Serial.println(topicName);
    }
    else {
      Serial.print("[MQTT] Connection failed with state ");
      Serial.println(mqttClient.state());
    }
}

void loop() {
  mqttClient.loop();
  long current_millis = millis();
  if(last_millis < (current_millis-WAIT_DELAY)) {
    last_millis = current_millis;

  }
}
