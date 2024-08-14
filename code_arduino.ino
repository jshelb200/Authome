//
// Authome - Système de supervision à distance des appareils électriques
// 
// Description : Ce programme permet de superviser et contrôler un moteur électrique via un microcontrôleur NodeMCU
// connecté à un réseau Wi-Fi. Il utilise le protocole MQTT pour la communication entre le microcontrôleur et une interface
// graphique (dashboard). Les données de température et d'humidité sont également envoyées via MQTT.
//
// Matériel :
// - NodeMCU v1
// - Capteur DHT11 (connecté au pin D1)
// - 2 relais
//
// Bibliothèques requises :
// - ESP8266WiFi.h : pour la connexion Wi-Fi
// - PubSubClient.h : pour la communication MQTT
// - DHT.h : pour la lecture des données du capteur DHT11
//
// Auteur : [Jerome EVI]
//

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <stdio.h> 

DHT dht;

// Mettre à jour ces valeurs selon votre réseau
const char* ssid = "CANALBOX-1CF2";
const char* password = "95327001461";
const char* mqtt_server = "192.168.1.129";   // Exemple : 192.168.0.19

WiFiClient espClient;
PubSubClient client(espClient);
char temperature[10];
char humidite[10];

void setup() {
  pinMode(2, OUTPUT);     // Initialisation de la LED intégrée comme sortie
  pinMode(5, OUTPUT);     // Direction droite du moteur
  pinMode(4, OUTPUT);     // Direction gauche du moteur
  dht.setup(D1);          // Pin des données du DHT11
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); // Le callback est exécuté à chaque message reçu depuis le dashboard
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  if (String(topic) == "topictest") {
    // Allume la LED si un '1' est reçu
    if ((char)payload[0] == '1') {
      Serial.println("LOW");
      digitalWrite(2, LOW); // Allume la LED (active LOW sur l'ESP-01)
    }
    if ((char)payload[0] == 'f')
      digitalWrite(4, LOW); // Arrêt gauche
    if ((char)payload[0] == 'c')
      digitalWrite(5, LOW); // Arrêt droite
    if ((char)payload[0] == 'c' && (char)payload[1] == 'g')
      digitalWrite(4, HIGH); // Tourne à gauche
    if ((char)payload[0] == 'f' && (char)payload[1] == 'd')
      digitalWrite(5, HIGH); // Tourne à droite
    delay(10);

    if ((char)payload[0] == '0') {
      digitalWrite(2, HIGH); // Éteint la LED
      digitalWrite(4, LOW);  // Arrêt gauche
      digitalWrite(5, LOW);  // Arrêt droit
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("topictest");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(dht.getMinimumSamplingPeriod()); // Délai équivalent à la période d'échantillonnage
  float humfloat = dht.getHumidity();    // Récupère la valeur d'humidité
  float temfloat = dht.getTemperature(); // Récupère la valeur de température
  sprintf(temperature, "%.1f", temfloat);
  sprintf(humidite, "%.1f", humfloat);
  client.publish("topictest/temp", temperature);
  client.publish("topictest/humidity", humidite);
}
