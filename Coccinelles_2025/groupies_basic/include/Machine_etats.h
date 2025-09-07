#ifndef MACHINE_ETATS_H
#define MACHINE_ETATS_H

#include <Arduino.h>
#include <Mesure_pos.h>
#include <Moteur.h>
#include <Irsensor.h>
#include <Asserv.h>
#include <Define_map.h>
#include "Serv.h"
#include "define.h"

#define K 1
#define dt 10

#define time_sensor 8000

class Machine_etats
{
    enum Pami_State
    {
        INIT,
        MOVE,
        STOP,
        END,

    };

public:
    Pami_State etat;
    long m_time;
    long m_time_global;
    long m_time_sensor;
    bool condx_turn;
    bool condy_turn;
    bool condx_arret;
    bool condy_arret;
    bool has_turned = false; // Indique si on a déjà tourné ou pas
    int fin_x;
    int fin_y;
    int turn_x;
    int turn_y;
    int fin_final_x;
    int fin_final_y;

    // public:
    int tirette = 1; // TODO Etat par défaut de la tirette , CHANGER SI NECESSAIRE
    int equipe = 1;
    int first = 0; // Tirette n'est pas tirée.

    float pos_init_x = STARTX; // TODO : A MODIFIER en foction de la stratégie
    float pos_init_y = STARTY; // TODO : A MODIFIER en foction de la stratégie

    float pos_finit_x = 0; // Premier point clef
    float pos_finit_y = 0; // Premier point clef

    float pos_x = 0;
    float pos_y = 0;
    float angle = 0;
    int m_minimum_distance = 1000;

    Asserv *m_p_asserv;
    Serv *m_p_servo;

    Mesure_pos *m_p_mesure_pos;
    Irsensor *m_p_irsensor ;

    Machine_etats(Asserv *p_asserv, Mesure_pos *p_mesure_pos, Irsensor *p_irsensor);
    void setup();
    void loop();
};

#endif
