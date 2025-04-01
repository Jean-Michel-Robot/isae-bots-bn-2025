/**
 * @file define_ewan.h
 * @brief fichier de configuration des pins pour la pami walle ( cramptesque :) )
 * Voir avec l'elec pour les pins
 */
// TODO REGLER LES PINS AVANT LA COUPE AVEC L'ELEC
#ifndef DEFINE_H
#define DEFINE_H

/*
ENCODEURS
*/
#define CLK_L 5 // CLK LEFT  ENCODER
#define DT_L 18 // DT LEFT Encoder

#define CLK_R 17 // CLK RIGHT ENCODER
#define DT_R 16  // DT RIGHT Encoder

/*
MOTEURS
*/

#define EN_R 27  // EN RIGHT MOTEUR
#define IN1_R 13 // IN1 RIGHT MOTEUR
#define IN2_R 12 // IN2 RIGHT MOTEUR

#define EN_L 26  // EN LEFT MOTEUR
#define IN1_L 15 // IN1 LEFT MOTEUR
#define IN2_L 14 // IN2 LEFT MOTEUR

/*
SENSORS
*/

/*
SERVO
*/
#define ANGLE1 20 ; 
#define ANGLE2 60 ;
#define TEMPS_BLINK 1 ; //Temps clignotement (secondes).

#endif