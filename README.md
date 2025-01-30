# 🔌 Authome - Supervision à Distance des Appareils Électriques

**Authome** est un projet de supervision et de contrôle d'appareils électriques à distance. Il permet d'interagir avec un moteur électrique à travers une interface graphique et de surveiller les conditions environnementales via un capteur DHT11.

## 🎯 Objectif du Projet
- Développer une interface intuitive pour la supervision et le contrôle à distance.
- Exploiter la puissance du **NodeMCU v1** et du protocole **MQTT** pour la communication.
- Assurer une gestion efficace des relais pour l'activation des appareils électriques.

## 🛠️ Composants Utilisés
- **NodeMCU v1** – Microcontrôleur WiFi pour la communication MQTT.
- **DHT11** – Capteur de température et d'humidité (connecté sur **D1**).
- **2 relais** – Pour contrôler les appareils électriques.

## 🚀 Installation et Configuration
### 1️⃣ **Téléversement du Code**
- Chargez le fichier **Arduino** sur votre **NodeMCU v1** en utilisant **Arduino IDE**.

### 2️⃣ **Importation du Fichier JSON**
- Importez le fichier **JSON** dans un nouveau projet **Node-RED** pour l'affichage et le contrôle.

### 3️⃣ **Configuration du Serveur Mosquitto**
- Installez **Mosquitto** sur **Debian** ou **Raspberry Pi** :
  ```sh
  sudo apt-get install mosquitto
  ```
- Utilisez le fichier de configuration fourni : **mosquitto.conf**.
- Démarrez le serveur MQTT avec la commande :
  ```sh
  mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf
  ```
- **Testez la communication MQTT** et vérifiez le bon fonctionnement du système. 🎉

## 📜 Détails du Projet
### **Software**
✅ Configuration et gestion du serveur **MQTT**.  
✅ Développement d'une **interface Node-RED** pour la supervision.  
✅ Programmation du **NodeMCU** avec **Arduino IDE**.  
✅ Établissement d'une communication fluide entre les différents blocs.  

### **Hardware**
✅ Conception d'un **circuit de commande** fiable et sécurisé.  
✅ Intégration des **capteurs et actionneurs** (DHT11 + relais).  

## 🔧 Commandes MQTT sous Linux
Créer une session MQTT avec la configuration :
```sh
mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf
```

---
⚡ **Supervisez vos appareils électriques facilement avec Authome !** 🔥

