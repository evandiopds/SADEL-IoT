#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


#define FIREBASE_HOST "host_firebase_aqui"
#define FIREBASE_AUTH "chave_firebase_aqui"

#define WIFI_SSID "wifi_ssid_aqui"
#define WIFI_PASSWORD "senha_wifi_aqui"


#define PINO_POT 34
#define PINO_LED 2

#define HEARTBEAT_INTERVAL 30000 
unsigned long lastHeartbeatTime = 0; 

#define ALERTA_THRESHOLD 3500
bool alarmeAtivo = false;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  pinMode(PINO_POT, INPUT);
  pinMode(PINO_LED, OUTPUT);

  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("Wi-Fi Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  configTime(-3 * 3600, 0, "pool.ntp.org");
  Serial.print("Sincronizando relógio NTP...");
  
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nRelógio Sincronizado!");
  
}

void enviarAlerta(const char* geoloc, const char* timeString, float confianca) {
  Serial.println("==================================");
  Serial.println("SOM DE MOTOSSERRA DETECTADO!");
  Serial.println("Enviando pacote de alerta para o Firebase...");

  FirebaseJson json;
  json.set("tipo_som_detectado", "motosserra");
  json.set("geoloc", geoloc);
  json.set("data_hora", timeString); 
  json.set("nivel_confianca", confianca);
  
  if (Firebase.RTDB.pushJSON(&fbdo, "/alertas", &json)) {
    Serial.println("ALERTA ENVIADO COM SUCESSO!");
    Serial.println(fbdo.pushName());
  } else {
    Serial.println("ERRO AO ENVIAR ALERTA:");
    Serial.println(fbdo.errorReason());
  }
  Serial.println("==================================");
}

void loop() {
  
  char timeString[20] = "ERRO_NTP";
  struct tm timeinfo;
  if(getLocalTime(&timeinfo)){
    strftime(timeString, sizeof(timeString), "%Y-%m-%dT%H:%M:%S", &timeinfo);
  }

  unsigned long currentTime = millis();
  if (currentTime - lastHeartbeatTime > HEARTBEAT_INTERVAL) {
    lastHeartbeatTime = currentTime;
    Serial.println(">>> Enviando Heartbeat (Ping)...");
    FirebaseJson statusJson;
    statusJson.set("last_seen", timeString); 
    if (!Firebase.RTDB.setJSON(&fbdo, "/status/sensor_chapada_01", &statusJson)) {
        Serial.println(">>> Falha ao enviar Heartbeat.");
    }
  }

  int valorPot = analogRead(PINO_POT);

  if (valorPot > ALERTA_THRESHOLD && !alarmeAtivo) {
    alarmeAtivo = true;
    digitalWrite(PINO_LED, HIGH);
    
    float confianca = map(valorPot, ALERTA_THRESHOLD, 4095, 70, 100) / 100.0;
    
    enviarAlerta("-7.249, -39.496", timeString, confianca);
  } 
  
  else if (valorPot < ALERTA_THRESHOLD && alarmeAtivo) {
    alarmeAtivo = false;
    digitalWrite(PINO_LED, LOW);
    Serial.println("Nível de som normalizado. Alarme resetado.");
  }
  
  else if (valorPot > ALERTA_THRESHOLD && alarmeAtivo) {
    digitalWrite(PINO_LED, HIGH);
  }

  delay(100);
}