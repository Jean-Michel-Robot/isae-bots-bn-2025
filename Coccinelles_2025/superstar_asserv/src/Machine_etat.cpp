#include <Machine_etats.h>
#include <Arduino.h>
#include <cmath>

#include <define.h>

Machine_etats::Machine_etats(Asserv *p_asserv, Mesure_pos *p_mesure_pos, Ultrason *p_ultrason)
{
    m_p_asserv = p_asserv;
    m_p_mesure_pos = p_mesure_pos;
    m_p_ultrason = p_ultrason;
}

void Machine_etats::setup()
{
    pinMode(4, INPUT);
    pinMode(READEQUIPE, INPUT);
    etat = INIT;
    m_time = millis();
    // Serial.println(m_time);
    m_time_global = millis();
    // Serial.println("setup fin");
}

void Machine_etats::loop()
{

    if (millis() - m_time >= dt) // Tout les dt
    {
        if (tirette == 1) // Si la tirette est toujours là, reset compteur à 0
        {
            m_time_global = millis();
        }

        // Lire l'état de la tirette
        tirette = digitalRead(4);

        // Lis dans quelle équipe est la pami (interrupteur)
        equipe = digitalRead(READEQUIPE);

        //  Récupère la distance au danger le plus proche
        m_p_ultrason->loop();
        m_minimum_distance = m_p_ultrason->m_distance;

        Serial.print("temps écoulé : dt = ");
        Serial.println(millis() - m_time_global);

        switch (etat) // Machine à etat
        {
        case INIT:
            if (millis() - m_time_global >= GLOBALTIME)
            {
                // Serial.println("end") ;
                m_p_asserv->asserv_global(0, 0, angle);
                etat = END;
            }
            else
            {
                if (equipe == 1)
                {
                    /*Coté gauche par rapport à scène*/
                    fin_x = GFIN_SUPERSTAR_X;
                    fin_y = GFIN_SUPERSTAR_Y;
                }
                else
                {
                    /*Coté droite par rapport à scène*/
                    fin_x = DFIN_SUPERSTAR_X;
                    fin_y = DFIN_SUPERSTAR_Y;
                }
                if ((millis() - m_time_global >= START_TIME) && tirette == 0)
                {
                    etat = MOVE;
                    // Serial.println("init");
                }
                else
                {
                    etat = INIT;
                }
            }
            break;
        case MOVE:

            if (millis() - m_time_global >= GLOBALTIME) // Si le match est terminé (T >= 100s)
            {
                // Serial.println("end") ;
                m_p_asserv->asserv_global(0, 0, angle); // Arrêt
                etat = END;
            }
            else
            {

                if ((m_minimum_distance >= 0.1) && (m_minimum_distance <= DISTANCE_MIN))
                {
                    etat = STOP;
                }
                else
                {
                    pos_x = m_p_mesure_pos->position_x + pos_init_x;
                    pos_y = m_p_mesure_pos->position_y + pos_init_y;
                    angle = atan2(pos_finit_y - pos_y, pos_finit_x - pos_x);

                    m_p_asserv->asserv_global(SPEED, SPEED, angle); // corrige l'angle.

                    condx_turn = (pos_x <= TOURNE_SUPERSTAR_X + EPSP) && (pos_x >= TOURNE_SUPERSTAR_X - EPSP);
                    condy_turn = (pos_y <= TOURNE_SUPERSTAR_Y + EPSP) && (pos_y >= TOURNE_SUPERSTAR_Y - EPSP); // A modifier pour faire cercle.
                    
                    if (condx_turn && condy_turn)
                    {
                        pos_finit_x = fin_x;
                        pos_finit_y = fin_y;
                        etat = MOVE;
                    }

                    condx_arret = (pos_x <= fin_x + EPSP) && (pos_x >= fin_x - EPSP);
                    condy_arret = (pos_y <= fin_y + EPSP) && (pos_y >= fin_y - EPSP); // A modifier pour faire cercle.

                    if (condx_arret && condy_arret)
                    {
                        etat = END;
                    }
                    else
                    {
                        etat = MOVE;
                    }
                }
            }
            break;

        case STOP: 
            // Serial.println("stop");
            if (millis() - m_time_global >= GLOBALTIME)
            {
                // Serial.println("end") ;
                m_p_asserv->asserv_global(0, 0, angle);
                etat = END;
            }
            else
            {
                m_p_asserv->asserv_global(0, 0, m_p_mesure_pos->position_theta);
                if ((m_minimum_distance <= 0.1) || (m_minimum_distance >= DISTANCE_MIN))
                {
                    etat = MOVE;
                }
                else
                {
                    etat = STOP;
                }
            }
            break;

        case END:
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, 0);

            // m_p_servo->blink(1, ANGLE1, ANGLE2) ;
            break;
        }
        m_time = millis();
    }
}