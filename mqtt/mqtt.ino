#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* rede = "SUA_REDE";
const char* senha = "SUA_SENHA";
WiFiClient wiFiClient;

const char* broker = "iot.eclipse.org";
int brokerPort = 1883;
const char* topico = "newton/tech-talk";
const char* id = "xablau";
PubSubClient mqttClient(wiFiClient);

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.print("Connecting to WIFI");

  WiFi.begin(rede, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WIFI");

  mqttClient.setServer(broker, brokerPort);

  pinMode(D2, INPUT_PULLUP);

}

void loop() {
  Serial.print("Connecting to MQTT");
  
  while (!mqttClient.connected()) {
    Serial.print("#");
    mqttClient.connect(id);
    delay(500);
  }

  Serial.println();
  Serial.println("Connected to MQTT");

  int botao = digitalRead(D2);

  if (botao) {
    mqttClient.publish(topico, "nao apertou", true);
  } else {
    mqttClient.publish(topico, "apertou", true);
  }
  delay(1000);
}

