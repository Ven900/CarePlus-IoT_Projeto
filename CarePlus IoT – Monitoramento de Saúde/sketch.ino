#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// ===== CONFIG =====
#define DHTPIN 15
#define DHTTYPE DHT22
#define LED_PIN 2

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===== HiveMQ Cloud =====
const char* mqtt_server = "69f6abff43544c939b482a9a4fc28581.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "careplusESP32";
const char* mqtt_pass = "MObawike90&*";

// ===== OBJETOS =====
WiFiClientSecure espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

// ===== WIFI =====
void setup_wifi() {
  Serial.print("WiFi conectando");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

// ===== MQTT =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT conectando...");

    String clientId = "careplus-" + String(random(1000, 9999));

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente...");
      delay(2000);
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000); // IMPORTANTE

  Serial.println("=== CarePlus iniciado ===");

  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  setup_wifi();

  espClient.setInsecure(); // necessário no Wokwi

  client.setServer(mqtt_server, mqtt_port);
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int bpm = random(60, 110);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Erro ao ler DHT!");
    delay(2000);
    return;
  }

  // ===== ALERTA =====
  bool alerta = false;

  if (temp > 37.5 || bpm > 95) {
    alerta = true;
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // ===== JSON =====
  String payload = "{";
  payload += "\"device\":\"careplus-watch\",";
  payload += "\"temperature\":" + String(temp) + ",";
  payload += "\"humidity\":" + String(hum) + ",";
  payload += "\"bpm\":" + String(bpm) + ",";
  payload += "\"alert\":" + String(alerta ? "true" : "false");
  payload += "}";

  // ===== LOG =====
  Serial.println("Enviando:");
  Serial.println(payload);

  // ===== MQTT =====
  if (client.publish("careplus/saude", payload.c_str())) {
    Serial.println("MQTT enviado com sucesso!");
  } else {
    Serial.println("Erro ao enviar MQTT!");
  }

  Serial.println("----------------------");

  delay(3000);
}