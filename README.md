
authomeproject

Systeme de supervion à distance des appareils Electriques

Resumé du projet de fin d'étude consistant à créer une interface graphique pour controler et superviser un moteur electrique. Composants -nodemcu v1 -DHT11 (Pin D1 du nodemcu) -2 relays Guide d'utilisation -le fichier arduino est à uploader dans un nodemcu(ici V1) -le fichier json à importer dans un noveau projet node-red ''mise au point du serveur mosquitto (mqtt) sous kali linux (kernel) -apt-get install mosquitto -la configuration est en piece jointe -mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf demarre le serveur avec la configuration mosqitto.conf tout devrait fonctionner maintenant euh.. normalement lol

Projet Authome ( Conception et réalisation d’un outil de supervision des appareils électriques.

Software :

    Configuration du serveur MQTT IOT protocol sous Debian
    Développement d’IHM pour la supervision des appareils sous NODE-RED
    Programmation d'une carte Nodemcu via Arduino IDE
    Mise en communication des différents blocs

Hardware :

    Conception du circuit de commande

command mqtt sous linux kernel

mosquitto -c /etc/mosquitto/conf.d/mosquitto.conf # por creer une session avec la configuration lister. configuration que je dois modifier si mon ip change ou je veux changer de port.

mosquitto_sub -h 192.168.228.3 -p 1883 -v -t 'topictest' -u nadik -P jarod2000 #creation du topic topictest avec user -u nadik ;)
