/**
 * @file main.cpp
 * @brief Programme principal , a implementer dans la pami
 * Pour faire du debug , decommenter les lignes suivient d'un #DEBUG
 *
 */
#include <Moteur.h>
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <Encodeur.h>
#include <Mesure_pos.h>
#include <Serv.h>
#include <define.h>
#include <Asserv.h>
#include <Irsensor.h>
#include <Machine_etats.h>

#define IR_PIN 4 //  ne sert à rien pour le moment , sert pour l'interruption


Irsensor irsensor = Irsensor(I2C_SDA, I2C_SCL); // Initialisation du capteur IR
Moteur moteur_d = Moteur(EN_R, IN1_R, IN2_R);
Moteur moteur_g = Moteur(EN_L, IN1_L, IN2_L);
Encodeur encoder_R = Encodeur(CLK_R, DT_R);
Encodeur encoder_L = Encodeur(CLK_L, DT_L);
Mesure_pos mesure_pos = Mesure_pos(&encoder_R, &encoder_L);
Asserv asserv = Asserv(&moteur_d, &moteur_g, &mesure_pos);
Serv servo = Serv(SERVPIN); // Initialisation du servo

Machine_etats machine_etats = Machine_etats(&asserv, &mesure_pos, &irsensor, &servo);

long m_time_log = 0; // Variable de temps ou on stocke le temps actuel

void setup()
{

  
  irsensor.setup();
  mesure_pos.setup();
  servo.setup(); // Initialisation du servo
  // Si on veut tester les encodeurs , on les setup
  
  
  encoder_L.setup();
  encoder_R.setup();
  

  Serial.begin(115200); // Initialisation de la communication série
  
  
  moteur_g.setup();     // Initialisation des moteurs
  moteur_d.setup();
  Serial.println("moteur setup");
  // Test moteur
  
  //moteur_g.set_speed(255); //TODO : regler la vitesse pour tester la vitesse max
  //moteur_d.set_speed(255);
  
 
  asserv.setup();
  
  Serial.println("asserv setup");
  machine_etats.setup();
  Serial.println("machine etats setup");

  m_time_log = millis();
  
}

void loop()
{
    
  //DEBUG
  //encoder_L.loop();
  //encoder_R.loop();
  
  irsensor.loop(); // Lecture du capteur IR
  mesure_pos.loop();
  //servo.loop();
  //  Serial.println("mesure pos loop");
  //  // #DEBUG Si on veut tester les asservissements , on decommente la lige suivante et on commente machine_etats.loop()
  // asserv.loop();
  machine_etats.loop();
  //servo.blink(1000, ANGLE1, ANGLE2); // Clignotement du servo
  //Serial.println("machie etats loop");
  // delay(100); // Delay de 100ms entre chaque boucle
  
  if(m_time_log + 2090 < millis()) // Log toutes les secondes
  {
    Serial.print("Vitesse L :");
    Serial.print(mesure_pos.vitesse_l);
    Serial.print(" Vitesse R :");
    Serial.print(mesure_pos.vitesse_r);
    Serial.print(" Pos X :");
    Serial.print(mesure_pos.position_x);
    Serial.print(" Pos Y :");
    Serial.print(mesure_pos.position_y);
    Serial.print(" Theta :");
    Serial.println(mesure_pos.position_theta);

    Serial.print(" Etat :");
    Serial.print(machine_etats.etat);
    Serial.print("   Angle machine à état :");
    Serial.print(machine_etats.angle);
    Serial.print("  Etape");
    Serial.println(machine_etats.pos_finit_x);
    m_time_log = millis();

  }
//le délai -pause des problèmes sur l'asserv !!
}
