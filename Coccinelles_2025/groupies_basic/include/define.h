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
//encodeur 2
#define CLK_R 4 // CLK LEFT  ENCODER
#define DT_R 16 // DT LEFT Encoder


//encodeur 1
#define CLK_L 18 // CLK RIGHT ENCODER
#define DT_L 19  // DT RIGHT Encoder

#define INV_L 0 // Inversion du sens de rotation de l'encodeur gauche
#define INV_R 0 // Inversion du sens de rotation de l'encodeur droit


/*
MOTEURS
*/
//moteur 2
#define EN_L 25  // EN RIGHT MOTEUR
#define IN1_L 27 // IN1 RIGHT MOTEUR
#define IN2_L 26 // IN2 RIGHT MOTEUR

//moteur 1
#define EN_R 13  // EN LEFT MOTEUR
#define IN1_R 12 // IN1 LEFT MOTEUR
#define IN2_R 14 // IN2 LEFT MOTEUR

/*
SENSORS
*/  

/*IR SENSOR*/
#define I2C_SDA 17
#define I2C_SCL 5

/*
SERVO
*/
#define ANGLE1 20  
#define ANGLE2 60 
#define TEMPS_BLINK 1  //Temps clignotement (secondes).
#define Serv_Pin 15 // A changer

/*
MACHINE A ETAT
*/
#define time_global 30000
#define START_TIME 85  //Les groupies commence dans les 15 dernières minutes.
#define DMIN 15 // En cm, à modifier.
#define EPSP 1 //Incertitude position, cm
#define EPSA 0.1 //0,1 ? //Incertitude position, radian
#define DMIN 15 // En cm, à modifier.
#define DMAX 30 //En cm, à modifier.
#define SPEED 20      // Vitesse en cm/s 25 est la vitesse max des moteurs
// c'est faux 25 n'est pas la vitesse max des moteurs, à trouver la bonne valeur (pour moi c'est 255)
#define DISTANCE_MIN 0 // Distance minimale pour éviter un obstacle en mm

#define STARTX 0
#define STARTY 0

/*** On a :
 * pami 1 : celle qui part en premier, va le plus au fond
 * pami 2 : celle qui part en deuxieme, va au milieu
 * pami 3 : celle qui part en dernière, va au plus proche
 */



/*ROBOT 3*/
#define START_TIME1 000  //Les groupies commence dans les 15 dernières secondes, commence juste après.

/*Coté gauche (équipe = 1)*/
#define TURNX3 80
#define TURNY3 7
#define FINX3 145
#define FINY3 7 


/*ROBOT 1*/
#define START_TIME2 85000  //Les groupies commence dans les 15 dernières secondes.

#define TURNX1 700
#define TURNY1 1625
#define FINX1 1400
#define FINY1 1400




#endif