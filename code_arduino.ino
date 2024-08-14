//evikodjojerome@gmail.com
//Projet de fin d'etude pour obtention de la licence
//Control et supervision de moteur industrielle à distance basé sur une carte nodemcu

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <stdio.h>// pour la convertion du float temp vers char publish

DHT dht;

// Update these with values suitable for your network.

const char* ssid =         "CANALBOX-1CF2";
const char* password =    "95327001461";
const char* mqtt_server = "192.168.1.129";   /// example 192.168.0.19

WiFiClient espClient;
PubSubClient client(espClient);
char temperature[3];
char humidite[3];

void setup() {
  pinMode(2, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(5, OUTPUT);     // direction droite du moteur
  pinMode(4, OUTPUT);     // direction gauche du moteur
  dht.setup(D1);// pin des donnés du dht11
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);// le void callback s'execute a chaque fois il y a une envoie depuis le dashboard. 
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  // Switch on the LED if an 1 was received as first character
   if ((char)payload[0] == '1') {
     Serial.println("LOW");
     digitalWrite(2, LOW);   // Turn the LED on (Note that LOW is the voltage level // but actually the LED is on; this is because // it is acive low on the ESP-01)
  }
   if ((char)payload[0] == 'f' )
          digitalWrite(4, LOW); // arret gauche
   if ((char)payload[0] == 'c' )
          digitalWrite(5, LOW); // arret droite
   if ((char)payload[0] == 'c'and (char)payload[1] == 'g' )
          digitalWrite(4, HIGH);//  active la pin 4 pour tourner a gauche
   if ((char)payload[0] == 'f'and (char)payload[1] == 'd' )
          digitalWrite(5, HIGH);//  active la pin 5 pour tourner a droite  
          delay(10);    
         

 if ((char)payload[0] == '0') {
    digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
    digitalWrite(4, LOW); // arret gauche
    digitalWrite(5, LOW); // arret droit
  }
  
}
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     //client.publish("topictest", "hello world");
      // ... and resubscribe
      client.subscribe("topictest");
      //client.subscribe("temp");
      //client.subscribe("humidity");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(dht.getMinimumSamplingPeriod());// Delay of amount equal to sampling period 
  float humfloat = dht.getHumidity();//Get humidity value 
  float temfloat = dht.getTemperature();//Get temperature value 
  sprintf(temperature, "%g", temfloat);
  sprintf(humidite, "%g", humfloat);
  client.publish("topictest/temp", temperature);
  client.publish("topictest/humidity", humidite);
  }
