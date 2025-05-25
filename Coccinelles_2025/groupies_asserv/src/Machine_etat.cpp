#include <Machine_etats.h>
#include <Arduino.h>
#include <cmath>


#include <define.h>


Machine_etats::Machine_etats(Asserv *p_asserv, Mesure_pos *p_mesure_pos, Irsensor *irsensor)
{
    m_p_asserv = p_asserv;
    m_p_mesure_pos = p_mesure_pos;
}

void Machine_etats::setup()
{
    pinMode(4, INPUT);
    etat = INIT;
    m_time = millis();
    Serial.println(m_time);
    m_time_global = millis();
    Serial.println("setup fin");
}

void Machine_etats::loop()
{
    Serial.println("herein") ;

    if (millis() - m_time >= dt)
    {   
        if (millis() - m_time_global >= time_global)
        {
            Serial.println("endh") ;
            m_p_asserv->asserv_global(0, 0, angle);
            etat = END;
        }
        // Lire l'état de la tirette
        tirette = digitalRead(4);
        Serial.print("tirette = ") ;
        Serial.println(tirette) ;
        // Récupère la distance au danger le plus proche
        //m_minimum_distance = m_p_ultrason->m_distance ;
        Serial.print("m_minimum_distance = ") ;
        Serial.println(m_minimum_distance) ;
        switch (etat)
        {
            case INIT:
            Serial.println(tirette) ;
            if ((millis() - m_time_global >= START_TIME) && tirette == 0) {
                m_time_global = millis() ;
                etat = MOVE ;
                Serial.println("init");
            } 
            else {
                etat = INIT ;
            }
            break;
        case MOVE:
            Serial.println("move");
            Serial.print("posex:");
            Serial.println(pos_x);
            Serial.print("poseY:");
            Serial.println(pos_y);
            if (m_minimum_distance <= DISTANCE_MIN) {
                etat = STOP;
                
            }
            
            pos_x = m_p_mesure_pos->position_x + pos_init_x;
            pos_y = m_p_mesure_pos->position_y + pos_init_y;
            angle = atan2(pos_y - pos_finit_y, pos_finit_x - pos_x);
            Serial.print("angle = ") ;
            Serial.println(angle);
            m_p_asserv->asserv_global(SPEED, SPEED, angle); //corrige l'angle. 
            
            condx_turn = (pos_x <= TURNX1 + EPSP) && (pos_x >= TURNX1 - EPSP) ;
            condy_turn = (pos_y <= TURNY1 + EPSP) && (pos_y >= TURNY1 - EPSP) ;
            if ( condx_turn && condy_turn) {
                pos_finit_x = FINX1 ;
                pos_finit_y = FINY1 ;
                pos_init_x = TURNX1 ;
                pos_init_y = TURNY1 ;
                m_p_mesure_pos->reinitialise() ;
                etat = MOVE ;
            }

            condx_arret = (pos_x <= FINX1 + EPSP) && (pos_x >= FINX1 - EPSP) ;
            condy_arret = (pos_y <= FINY1 + EPSP) && (pos_y >= FINY1 - EPSP) ;
            if (condx_arret && condy_arret) {
                etat = END ;
            }
            else {
                etat = MOVE ;
            }
            break;

        case STOP:
            Serial.println("stop");
            m_p_asserv->asserv_global(0, 0, 0);
            if (m_minimum_distance > DISTANCE_MIN)
            {
                etat = MOVE ;
            }
            else {
                etat = STOP ;
            }
            break;

        case END:
            Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, 0);
            m_p_servo->blink(1, ANGLE1, ANGLE2) ;
            break;

        }
        m_time = millis();
    }
}