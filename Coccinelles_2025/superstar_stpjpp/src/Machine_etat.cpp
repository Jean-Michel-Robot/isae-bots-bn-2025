#include <Machine_etats.h>
#include <Arduino.h>
#include <cmath>

#include <define.h>

Machine_etats::Machine_etats(Asserv *p_asserv, Mesure_pos *p_mesure_pos)
{
    m_p_asserv = p_asserv;
    m_p_mesure_pos = p_mesure_pos;
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

    if (millis() - m_time >= dt)
    {
        if (tirette == 1)
        {
            m_time_global = millis();
        }

        // Lire l'état de la tirette
        tirette = digitalRead(4);
        equipe = digitalRead(READEQUIPE);
        // Serial.print("tirette = ") ;
        // Serial.println(tirette) ;
        //  Récupère la distance au danger le plus proche
        //m_p_ultrason->loop();

        // //Serial.print("etat = ") ;
        // //Serial.println(etat) ;
        // //Serial.println();

        Serial.print("tps écoulé :");
        Serial.println(millis() - m_time_global);

        switch (etat)
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
            // Serial.println("move");
            // Serial.print("posex:");
            // Serial.println(pos_x);
            // Serial.print("poseY:");
            // Serial.println(pos_y);
            if (millis() - m_time_global >= GLOBALTIME)
            {
                // Serial.println("end") ;
                m_p_asserv->asserv_global(0, 0, angle);
                etat = END;
            }
            else
            {

                pos_x = m_p_mesure_pos->position_x + pos_init_x;
                pos_y = m_p_mesure_pos->position_y + pos_init_y;
                angle = atan2(pos_finit_y - pos_y, pos_finit_x - pos_x);
                // Serial.print("angle = ") ;
                // Serial.println(angle);
                m_p_asserv->asserv_global(SPEED, SPEED, angle); // corrige l'angle.

                condx_turn = (pos_x <= TOURNE_SUPERSTAR_X + EPSP) && (pos_x >= TOURNE_SUPERSTAR_X - EPSP);
                condy_turn = (pos_y <= TOURNE_SUPERSTAR_Y + EPSP) && (pos_y >= TOURNE_SUPERSTAR_Y - EPSP); // A modifier pour faire cercle.

                if (condx_turn && condy_turn)
                {
                    pos_finit_x = fin_x;
                    pos_finit_y = fin_y;
                    m_time_recul = millis();
                    etat = RECUL;
                }

                condx_arret = (pos_x <= fin_x + EPSP) && (pos_x >= fin_x - EPSP);
                condy_arret = (pos_y <= fin_y + EPSP) && (pos_y >= fin_y - EPSP); // A modifier pour faire cercle.
                if (condx_arret && condy_arret)
                {
                    Serial.println("RECULLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
                    etat = END;
                }
                else
                {
                    etat = MOVE;
                }
            }
            break;
        case RECUL:
            if ((millis() - m_time_recul) <= TIMERECUL)
            {
                pos_x = m_p_mesure_pos->position_x + pos_init_x;
                pos_y = m_p_mesure_pos->position_y + pos_init_y;
                angle = atan2(pos_finit_y - pos_y, pos_finit_x - pos_x);
                if (has_turned == 1)
                {
                    m_p_asserv->asserv_global(0, 0, M_PI / 2);
                    etat = RECUL;
                    if ((millis() - m_time_recul) >= 500)
                    {
                        has_turned = 0;
                    }
                }
                else
                {
                    m_p_asserv->asservissement(-SPEED, -SPEED);
                    etat = RECUL;
                }
            }
            else
            {
                etat = MOVE;
            }

        case END:
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, m_p_mesure_pos->position_theta);
            // m_p_servo->blink(1, ANGLE1, ANGLE2) ;
            break;
        }
        m_time = millis();
    }
}