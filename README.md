# Authome

**Système de supervision à distance des appareils électriques**

Ce projet de fin d'études consiste à créer une interface graphique pour contrôler et superviser un moteur électrique.

## Composants

- NodeMCU v1
- DHT11 (connecté au pin D1 du NodeMCU)
- 2 relais

## Guide d'utilisation

1. **Téléversement du code :** Uploadez le fichier Arduino sur un NodeMCU (ici V1).
2. **Importation du fichier JSON :** Importez le fichier JSON dans un nouveau projet Node-RED.
3. **Configuration du serveur Mosquitto :**

   - Installez Mosquitto [Debian] ou Raspberry :

     ```bash
     sudo apt-get install mosquitto
     ```

   - La configuration est fournie dans mosquitto.conf.
   - Pour démarrer le serveur avec la configuration `mosquitto.conf`, utilisez la commande suivante :

     ```bash
     mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf
     ```

   Tout devrait fonctionner maintenant... enfin, normalement ! 😊

## Détails du Projet Authome

### Objectif

Conception et réalisation d’un outil de supervision des appareils électriques.

### Software

- Configuration du serveur MQTT
- Développement d’IHM pour la supervision des appareils sous Node-RED
- Programmation d'une carte NodeMCU via Arduino IDE
- Mise en communication des différents blocs

### Hardware

- Conception du circuit de commande

## Commandes MQTT sous Linux (Kernel)

- **Créer une session avec la configuration :**

  ```bash
  mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf
