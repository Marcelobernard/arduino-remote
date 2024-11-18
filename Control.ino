#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "nome wifi";
const char* password = "senha wifi";

ESP8266WebServer server(80);

const int motor1PinA = D1;
const int motor1PinB = D2;
const int motor2PinA = D3;
const int motor2PinB = D4;

void setupMotors() {
  pinMode(motor1PinA, OUTPUT);
  pinMode(motor1PinB, OUTPUT);
  pinMode(motor2PinA, OUTPUT);
  pinMode(motor2PinB, OUTPUT);
}

// Funções de controle
void moveForward() {
  digitalWrite(motor1PinA, HIGH);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, HIGH);
  digitalWrite(motor2PinB, LOW);
}

void moveBackward() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, HIGH);
}

void turnLeft() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);
  digitalWrite(motor2PinA, HIGH);
  digitalWrite(motor2PinB, LOW);
}

void turnRight() {
  digitalWrite(motor1PinA, HIGH);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, HIGH);
}

void stopMotors() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, LOW);
}

void handleControl() {
  if (server.hasArg("plain")) {
    String command = server.arg("plain");
    Serial.println("Comando recebido: " + command);

    if (command == "\"forward\"") {
      moveForward();
    } else if (command == "\"backward\"") {
      moveBackward();
    } else if (command == "\"left\"") {
      turnLeft();
    } else if (command == "\"right\"") {
      turnRight();
    } else if (command == "\"stop\"") {
      stopMotors();
    } else {
      Serial.println("Comando inválido!");
    }

    server.send(200, "text/plain", "Comando recebido");
  } else {
    server.send(400, "text/plain", "Comando não recebido");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado ao WiFi!");
  Serial.println("IP address: " + WiFi.localIP().toString());

  setupMotors();
  server.on("/control", HTTP_POST, handleControl);
  server.begin();
}

void loop() {
  server.handleClient();
}
