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
#define CLK_R 18 // CLK LEFT  ENCODER
#define DT_R 19 // DT LEFT Encoder


//encodeur 1
#define CLK_L 4 // CLK RIGHT ENCODER
#define DT_L 16  // DT RIGHT Encoder

#define INV_L 0 // Inversion du sens de rotation de l'encodeur gauche
#define INV_R 1 // Inversion du sens de rotation de l'encodeur droit


/*
MOTEURS
*/
//moteur 2
#define EN_L 25  // EN RIGHT MOTEUR
#define IN1_L 26 // IN1 RIGHT MOTEUR
#define IN2_L 27 // IN2 RIGHT MOTEUR

//moteur 1
#define EN_R 13  // EN LEFT MOTEUR
#define IN1_R 12 // IN1 LEFT MOTEUR
#define IN2_R 14 // IN2 LEFT MOTEUR

/*
SENSORS
*/  

/*IR SENSOR*/
#define I2C_SDA 21
#define I2C_SCL 22

/*
SERVO
*/
#define ANGLE1 20  
#define ANGLE2 60 
#define TEMPS_BLINK 1  //Temps clignotement (secondes).
#define Serv_Pin 5 // A changer

/*
MACHINE A ETAT
*/
#define START_TIME 85  //Les groupies commence dans les 15 dernières minutes.
#define DMIN 15 // En cm, à modifier.
#define EPSP 1 //Incertitude position, cm
#define EPSA 0.1 //0,1 ? //Incertitude position, radian
#define DMIN 15 // En cm, à modifier.
#define DMAX 30 //En cm, à modifier.
#define STARTX 0
#define STARTY 0
/*ROBOT DERRIERE*/
#define START_TIME1 88  //Les groupies commence dans les 15 dernières secondes, commence juste après.
#define STARTX1 100 //temp
#define STARTY1 1750 //temp
#define TURNX1 900
#define TURNY1 1600
#define FINX1 1100
#define FINY1 1500 
/*ROBOT DEVANT*/
#define START_TIME2 85  //Les groupies commence dans les 15 dernières secondes.
#define STARTX2 100 //temp
#define STARTY2 1625 //temp
#define TURNX2 700
#define TURNY2 1625
#define FINX2 1400
#define FINY2 1400




#endif