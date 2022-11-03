#include <SPI.h>
#include <RF24.h>
String serialMessage = "";
#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE12"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel
const char message[] = "droite";     // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)
const char message2[] = "gauche";     // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)

void setup() {
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.setChannel(4);
  radio.stopListening();  
  Serial.begin(9600);            // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
}

void loop() {
  while(Serial.available()>0){
    serialMessage = Serial.readString();
    Serial.println(serialMessage);
    int str_len = serialMessage.length() + 1; 

// Prepare the character array (the buffer) 
char char_array[str_len];
 
// Copy it over 
serialMessage.toCharArray(char_array, str_len);
    radio.write(&char_array, sizeof(char_array));
  }
  //  radio.write(&message, sizeof(message));
}