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
#define CLK_R 22 // CLK LEFT  ENCODER
#define DT_R 21 // DT LEFT Encoder

#define CLK_L 16 // CLK RIGHT ENCODER
#define DT_L 13  // DT RIGHT Encoder

#define INV_L 0 // Inversion du sens de rotation de l'encodeur gauche
#define INV_R 0 // Inversion du sens de rotation de l'encodeur droit





/*
MOTEURS
*/

#define EN_L 14  // EN RIGHT MOTEUR
#define IN1_L 27 // IN1 RIGHT MOTEUR
#define IN2_L 26 // IN2 RIGHT MOTEUR

#define EN_R 33  // EN LEFT MOTEUR
#define IN1_R 32 // IN1 LEFT MOTEUR
#define IN2_R 25 // IN2 LEFT MOTEUR

/*
SENSORS
*/

/*
SERVO
*/
#define SERVPIN 34 // Broche du servo moteur sur D15
#define ANGLE1 20  
#define ANGLE2 60 
#define TEMPS_BLINK 1  //Temps clignotement (secondes).

/*
MACHINE A ETAT
*/

//Le coté est défini quand on estface à la scène.
// equipe = 1 : on est du coté gauche.
// equipe = 0 : on est du coté droit.


#define WEQUIPE 5 
#define READEQUIPE 17 //temp, pas trop compris lelien entre les deux.

#define GLOBALTIME 100000 // Temps global de la pami en ms 
#define START_TIME 85000  //Les pamis commencent dans les 15 dernières minutes.
#define SPEED 20      // Vitesse en cm/s 25 est la vitesse max des moteurs
// c'est faux 25 n'est pas la vitesse max des moteurs, à trouver la bonne valeur (pour moi c'est 255)
#define DISTANCE_MIN 20 // Distance minimale pour éviter un obstacle en mm
#define EPSP 0.5 //Incertitude position, cm
#define EPSA 0.1 //0,1 ? //Incertitude position, radian

#define DEPART_SUPERSTAR_X 0
#define DEPART_SUPERSTAR_Y 0
#define TOURNE_SUPERSTAR_X 116    
#define TOURNE_SUPERSTAR_Y 0 //Position ou la superstar va tourner

/***Coté gauche (equipe = 1)***/
#define GFIN_SUPERSTAR_X 116
#define GFIN_SUPERSTAR_Y -31.5 //position finale superstar

/***Coté droit (equipe = 0)***/
#define DFIN_SUPERSTAR_X 116
#define DFIN_SUPERSTAR_Y 31.5 //position finale superstar

/*
Capteur ultrason
*/
#define ECHO 7 // Broche Echo du HC-SR04 sur D7 //
#define TRIGGER 8 // Broche Trigger du HC-SR04 sur D8 //
#define DIST_MAX = 300; // Distance maxi a mesurer //
#define DIST_MINs = 3; // Distance mini a mesurer //



#endif