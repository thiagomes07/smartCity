#include <SPI.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Configurações Wi-Fi
const char* ssid = "GABRIEL_HMA_7524";
const char* password = "19#O04y4";

// Configurações MQTT com TLS
const char* mqtt_server = "b3756ca92cb74c75bee7c8288a87cb33.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "ESP32backend987123";
const char* mqtt_password = "Iotrackers32!";

const char* ca_cert = \
  "-----BEGIN CERTIFICATE-----\n" \
  "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\n" \
  "-----END CERTIFICATE-----";

WiFiClientSecure secureClient;
PubSubClient client(secureClient);

// Pinos dos LEDs
#define LED_RED_PIN 16
#define LED_GREEN_PIN 18
#define LED_YELLOW_PIN 17

// Pino do sensor de luminosidade (LDR)
#define LDR_PIN 33
#define LUMINOSIDADE_LIMITE 500 // Ajuste conforme necessário

void setup_wifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
    }
    Serial.println("Wi-Fi conectado!");
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Tentando conectar ao MQTT...");
        if (client.connect("ESP32Client01", mqtt_user, mqtt_password)) {
            Serial.println("Conectado ao broker MQTT!");
            client.subscribe("ponderada/semaforos");
        } else {
            Serial.print("Falha na conexão MQTT. Código de erro: ");
            Serial.println(client.state());
            delay(1500);
        }
    }
}

void callback(char* topic, byte* message, unsigned int length) {
    String response = "";

    // Concatena a mensagem recebida
    for (unsigned int i = 0; i < length; i++) {
        response += (char)message[i];
    }

    // Verifica se o tópico corresponde ao esperado
    if (String(topic) == "ponderada/semaforos") {
        Serial.print("Mensagem recebida no tópico: ");
        Serial.println(topic);
        Serial.print("Mensagem: ");
        Serial.println(response);

        // Lógica do semáforo
        if (response == "carro detectado") {
            digitalWrite(LED_GREEN_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, HIGH);
            delay(1000);
            digitalWrite(LED_YELLOW_PIN, LOW);
            digitalWrite(LED_RED_PIN, HIGH);
            delay(7000);
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, HIGH);
        }
    }
}

void checkLuminosidade() {
    int luminosidade = analogRead(LDR_PIN);
    Serial.print("Luminosidade atual: ");
    Serial.println(luminosidade);

    if (luminosidade < LUMINOSIDADE_LIMITE) {
        Serial.println("Baixa luminosidade detectada. Publicando mensagem 'noite'...");
        client.publish("ponderada/semaforos", "noite");

        // Pisca o LED amarelo por 15 segundos
        for (int i = 0; i < 15; i++) {
            digitalWrite(LED_YELLOW_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            delay(500);
            digitalWrite(LED_YELLOW_PIN, LOW);
            delay(500);
        }
    }
    digitalWrite(LED_GREEN_PIN, HIGH);
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_YELLOW_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);

    // Inicializa os LEDs
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH); // Inicia com verde
    digitalWrite(LED_YELLOW_PIN, LOW);

    setup_wifi();
    secureClient.setCACert(ca_cert);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Verifica a luminosidade periodicamente
    checkLuminosidade();

    delay(1000); // Evita verificações muito rápidas
}