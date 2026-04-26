#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== CONFIG =====
#define DHTPIN 15
#define DHTTYPE DHT22
#define LED_PIN 2
#define BUZZER 4
#define BUTTON 18

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "69f6abff43544c939b482a9a4fc28581.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "careplusESP32";
const char* mqtt_pass = "MObawike90&*";

WiFiClientSecure espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

// ===== VAR =====
int bpm = 70;
unsigned long lastBlink = 0;
bool ledState = false;

// ===== WIFI =====
void setup_wifi() {
  Serial.print("WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" conectado!");
}

// ===== MQTT =====
void reconnect() {
  while (!client.connected()) {
    String clientId = "careplus-" + String(random(1000, 9999));

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("MQTT conectado");
    } else {
      Serial.print("Erro MQTT: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  dht.begin();

  // OLED I2C
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  setup_wifi();

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("=== CarePlus FINAL ===");
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // BOTÃO = simula BPM alto
  if (digitalRead(BUTTON) == LOW) {
    bpm = random(100, 130);
  } else {
    bpm = random(60, 80);
  }

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Erro sensor");
    return;
  }

  // ===== STATUS =====
  String status = "NORMAL";

  if (temp > 38.5 || bpm > 120) {
    status = "CRITICO";
  }
  else if (temp > 38 || bpm > 110) {
    status = "ALERTA";
  }
  else if (temp > 37.2 || bpm > 95) {
    status = "CUIDADO";
  }

  // ===== ALERTAS =====
  if (status == "NORMAL") {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER);
  }
  else if (status == "CUIDADO") {
    digitalWrite(LED_PIN, HIGH);
    noTone(BUZZER);
  }
  else if (status == "ALERTA") {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 1000);
  }
  else if (status == "CRITICO") {
    if (millis() - lastBlink > 300) {
      lastBlink = millis();
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
    tone(BUZZER, 2000);
  }

  // ===== DISPLAY =====
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("CarePlus Monitor");

  display.setCursor(0, 12);
  display.print("Temp: ");
  display.println(String(temp, 1));

  display.setCursor(0, 24);
  display.print("Hum: ");
  display.println(String(hum, 1));

  display.setCursor(0, 36);
  display.print("BPM: ");
  display.println(bpm);

  display.setCursor(0, 48);
  display.print("Estado: ");
  display.println(status);

  display.display();

  // ===== JSON =====
  String payload = "{";
  payload += "\"temp\":" + String(temp,1) + ",";
  payload += "\"hum\":" + String(hum,1) + ",";
  payload += "\"bpm\":" + String(bpm) + ",";
  payload += "\"status\":\"" + status + "\"";
  payload += "}";

  Serial.println(payload);

  client.publish("careplus/saude", payload.c_str());

  delay(2000);
}