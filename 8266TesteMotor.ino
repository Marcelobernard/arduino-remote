#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "***";
const char* password = "***";

ESP8266WebServer server(80);

#define MOTOR_PIN D7

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.on("/HIGH", []() {
    digitalWrite(MOTOR_PIN, HIGH);
    server.send(200, "text/plain", "Roda ativada");
    Serial.println("Comando recebido: HIGH");
  });

  server.on("/LOW", []() {
    digitalWrite(MOTOR_PIN, LOW);
    server.send(200, "text/plain", "Roda desativada");
    Serial.println("Comando recebido: LOW");
  });

  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();
}
