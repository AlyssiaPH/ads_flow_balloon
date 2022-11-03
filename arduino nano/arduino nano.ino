char message[32]; // for incoming serial data
#include <Servo.h>  // on inclut la bibliothèque servo
#include <SPI.h>
#include <RF24.h>
#include"pitches.h"
//THE SCREWDRIVER
#define pinCE     7
#define pinCSN    8  
#define musicPin  3
int speed=100;
#define tunnel1 "PIPE12"  // Avec cette librairie, on est "limité" à 32 caractères par message
RF24 radio(pinCE, pinCSN); 
const byte adresses[][6] = {tunnel1};
Servo servoMoteurGauche;
Servo servoMoteurDroite;
String stringMessage;


int noteDurationsMP[] = {       //duration of the notes
8,4,8,4,
4,4,4,12,
4,4,4,4,4,4,
4,16,4,

8,4,8,4,
4,2,1,1,2,1,1,12,
4,4,4,4,4,4,
4,16,4,

4,4,4,4,4,4,
4,4,4,12,
4,4,4,4,4,4,
4,4,4,12,

4,4,4,4,4,4,
2,1,1,2,1,1,4,8,4,
2,6,4,2,6,4,
2,1,1,16,4,

4,8,4,4,4,
4,16,4,
4,8,4,4,4,
4,20,
};
int melodyMP[] = {
NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,                   
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                 

NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                       

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, 0,
NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, END

};



int melodyGOT[] = {
  NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_G3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_G3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_G3,NOTE_B3,NOTE_F4,END
};
int noteDurationsGOT[]= {
  12,12,2,2,8,8,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,4,4,12
};
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, adresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(4);
  radio.startListening();

  }

void loop() {
  if(radio.available()) {                                                 // On regarde si une donnée a été reçue
      radio.read(&message, sizeof(message)); 
      Serial.println(message); // Lecture des données reçues, une par une
    String stringMessage=String(message);
    int messageInt=stringMessage.toInt();
    // read the incoming byte:
    if(messageInt==7){
      servoMoteurGauche.attach(2);
      delay(500);

      servoMoteurGauche.write(0);
      delay(500);
      servoMoteurGauche.write(60);
      delay(500);

      servoMoteurGauche.detach();

    }
    else if(messageInt == 8){
      servoMoteurDroite.attach(4);
      delay(500);

      servoMoteurDroite.write(0);
      delay(500);
      servoMoteurDroite.write(60);
      delay(500);

      servoMoteurDroite.detach();
    }
    else if(messageInt==9){
      servoMoteurGauche.attach(2);
      servoMoteurDroite.attach(4); 
      delay(500);
      servoMoteurGauche.write(0);
      servoMoteurDroite.write(60);
      delay(500);
      servoMoteurGauche.write(60);
      servoMoteurDroite.write(0);
      delay(500);
      servoMoteurGauche.detach();
      servoMoteurDroite.detach();
    }
    else if(messageInt==4){
      for (int thisNote = 0; melodyMP[thisNote]!=-1; thisNote++) {
        int noteDuration = speed*noteDurationsMP[thisNote];
        tone(musicPin, melodyMP[thisNote],noteDuration*.95);
        delay(noteDuration);
      }
    }
    else if(messageInt==5){
      for (int thisNote = 0; melodyGOT[thisNote]!=-1; thisNote++) {
        int noteDuration = speed*noteDurationsGOT[thisNote];
        tone(musicPin, melodyGOT[thisNote],noteDuration*.95);
        delay(noteDuration);
      }
    }
  }
}
