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
#define SERVPIN 15 // Pin du servo, à changer si nécessaire
#define ANGLE1 30  
#define ANGLE2 120 
#define TEMPS_BLINK 1  //Temps clignotement (secondes).
#define Serv_Pin 15 // A changer

/*
MACHINE A ETAT
*/

#define EQUIPE 22 // Pin changement de côté.
#define TIMEGLOBAL 1e5 // Temps global en ms, à modifier pour la compétition (100 secondes)


#define EPSP 1 //Incertitude position, cm
#define EPSA 0.1 //0,1 ? //Incertitude position, radian
#define DMAX 30 //En cm, à modifier.
#define SPEED 20      // Vitesse en cm/s 25 est la vitesse max des moteurs
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
#define START_TIME3 92000  //Les groupies commence dans les 15 dernières secondes, commence juste après.

/*Côté gauche (équipe = 1)*/
#define GTURNX3 45
#define GTURNY3 6
#define GFINX3 150
#define GFINY3 20
/*Côté droit (équipe = 0)*/
#define DTURNX3 45
#define DTURNY3 -6
#define DFINX3 150
#define DFINY3 -20  


/*ROBOT 2 (milieu)*/
#define START_TIME2 5000  //Les groupies commence dans les 15 dernières secondes.

/*Côté gauche (équipe = 1)*/
#define GTURNX2 80
#define GTURNY2 10
#define GFINX2 145
#define GFINY2 10
/*Côté droit (équipe = 0)*/
#define DTURNX2 80
#define DTURNY2 -10
#define DFINX2 145
#define DFINY2 -10  


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