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

//moteur 1s
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
#define SERVPIN 15 // Pin du servo, à changer si nécessaire
#define ANGLE1 20  
#define ANGLE2 320 
#define TEMPS_BLINK 2000  //Temps clignotement (secondes).


/*
MACHINE A ETAT
*/

#define EQUIPE 22 // Pin changement de côté.
#define TIMEGLOBAL 97000 // Temps global en ms, à modifier pour la compétition (100 secondes)


#define EPSP 0.7 //Incertitude position, cm
#define EPSA 0.1 //0,1 ? //Incertitude position, radian
#define DMAX 30 //En cm, à modifier.
#define SPEED 18      // Vitesse en cm/s 25 est la vitesse max des moteurs
// c'est faux 25 n'est pas la vitesse max des moteurs, à trouver la bonne valeur (pour moi c'est 255)
#define DISTANCE_MIN 60 // Distance minimale pour éviter un obstacle en mm

#define STARTX 0
#define STARTY 0

/*** On a :
 * pami 1 : celle qui part en premier, va le plus au fond
 * pami 2 : celle qui part en deuxieme, va au milieu
 * pami 3 : celle qui part en dernière, va au plus proche
 */



/*ROBOT 3 (derrière)*/
#define START_TIME3 85000  //Les groupies commence dans les 15 dernières secondes, commence juste après.

/*Côté gauche (équipe = 1)*/
#define GTURNX3 83
#define GTURNY3 38
#define GFINX3 111
#define GFINY3 38
/*Côté droit (équipe = 0)*/
#define DTURNX3 83
#define DTURNY3 -38
#define DFINX3 111
#define DFINY3 -38  


/*ROBOT 2 (milieu)*/
#define START_TIME2 85000  //Les groupies commence dans les 15 dernières secondes.

/*Côté gauche (équipe = 1)*/
#define GTURNX2 90
#define GTURNY2 30
#define GFINX2 135
#define GFINY2 30
/*Côté droit (équipe = 0)*/
#define DTURNX2 90
#define DTURNY2 -30
#define DFINX2 135
#define DFINY2 -30  


/*ROBOT 1 (devant)*/
#define START_TIME1 85000  //Les groupies commence dans les 15 dernières secondes.

/*Côté gauche (équipe = 1)*/
#define GTURNX1 80
#define GTURNY1 7
#define GFINX1 190
#define GFINY1 7
/*Côté droit (équipe = 0)*/
#define DTURNX1 80
#define DTURNY1 -7
#define DFINX1 190
#define DFINY1 -7  



#endif