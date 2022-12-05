#include <Arduino.h>
#include <WIFIConnector_MKR1000.h>
#include <MQTTConnector.h>



int etat=0;  //connatre l'état de la LED
int val=0;  //stocker le "niveau" de son traduit en niveau électrique
int led=3;  //controler la LED
const int MS_DELAI = 1000;   

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // Activation du port série pour affichage dans le moniteur série

  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();                  //Branchement au broker MQTT

}

void loop() {
  // put your main code here, to run repeatedly:
  val=analogRead(A0);  //le capteur est relié en A0       
  if(val>=12) {  //si le son dépasse 12
    if(etat==1) {  //et que la LED est allumée
      etat=0;  //on met l'état à 0
      analogWrite(led,LOW);  //et on éteint la LED
    }
    else {  //si la LED est éteinte
      etat=1;  //on met l'état à 1
      analogWrite(led,HIGH);  //et on allume la LED
     }
  }
  delay(100);  //on atteint 100 millisecondes pour ne pas surcharger la carte

  // impression dans le moniteur serie

  Serial.print("La valeur de son sortie est : ");
  Serial.print(val);
  appendPayload("son", val);  //Ajout de la donnée température au message MQTT
  sendPayload();                                   //Envoie du message via le protocole MQTT

  delay(MS_DELAI);    
}