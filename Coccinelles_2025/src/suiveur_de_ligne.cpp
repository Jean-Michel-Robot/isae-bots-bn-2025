//Machine à état pour robot suiveur de ligne.

#include <Machine_etats.h>
#include <Arduino.h>
#include <cmath>
#include "trajectories/PathTrajectory.hpp"
#include "Serv.h"
#include "suiveur_de_ligne.h"

Machine_etats_sl::Machine_etats_sl(Asserv *p_asserv, Irsensor *p_ir_sensor, Serv *p_servo)
{
    m_p_asserv = p_asserv;
    m_p_ir_sensor = p_ir_sensor;
    m_p_servo = p_servo ;
}

void Machine_etats_sl::setup()
{
    pinMode(34, INPUT);
    etat = INIT;
    m_time = millis();
    m_time_global = millis();
}

void Machine_etats_sl::loop()
{
    int INL = 4 ;
    int INR = 5 ;
    if (millis() - m_time >= dt) {
        int lsensor = analogRead(INL); //Valeur capteur gauche.
        int rsensor = analogRead(INR); //Valeur capteur droit.

        if (millis() - m_time_global >= time_global)
        {
            m_p_asserv->asservissement(0, 0);
            etat = END; //Tps dépassé.
        }
        // Lire l'état de la tirette
        tirette = digitalRead(34);
        Serial.println(tirette);

        // Récupère la distance au danger le plus proche
        m_minimum_distance = m_p_ir_sensor->ir_minimum_distance ;
        
       
        switch (etat)
        {
        case INIT:
            if (tirette == 0) {
                m_time_global = millis();
                etat = STRAIGHT ;
            } 
            else {
                etat = INIT ;
            }
            break;
        case STRAIGHT:
            m_p_asserv->asservissement(SPEED, SPEED);
            if (m_minimum_distance <= DISTANCE_MIN) {
                etat = STOP ;
            } 
            else if (lsensor > white_min && rsensor < black_max) {
                etat = TRIGHT ;
            }
            else if (rsensor > white_min && lsensor < black_max) {
                etat = TLEFT ;
            }
            else if (rsensor > white_min && lsensor > white_min) {
                etat = END ;
            }
            else {
                etat = STRAIGHT ;
            }
            break;

        case TLEFT:
            m_p_asserv->asservissement(20, 5);
            if (m_minimum_distance <= DISTANCE_MIN) {
                etat = STOP ;
            }
            else if (rsensor < black_max && lsensor < black_max) {
                etat = STRAIGHT ;
            }
            else if (rsensor > white_min && lsensor > white_min) {
                etat = END ;
            }
            else {
                etat = TLEFT ;
            }
            break;
        
        case TRIGHT:
            m_p_asserv->asservissement(5, 20);
            if (m_minimum_distance <= DISTANCE_MIN) {
                etat = STOP ;
            }
            else if (rsensor < black_max && lsensor < black_max) {
                etat = STRAIGHT ;
            }
            else if (rsensor > white_min && lsensor > white_min) {
                etat = END ;
            }
            else {
                etat = TRIGHT ;
            }            
            break;

        case STOP:
            m_p_asserv->asservissement(0, 0);
            if (m_minimum_distance > DISTANCE_MIN)
            {
                etat = STRAIGHT;
            }
            break;

        case END:
            m_p_asserv->asservissement(0, 0) ;
            m_p_servo->blink(1,25,25) ;//Wtf jcp.
            break;
        }
        m_time = millis();
    }
}