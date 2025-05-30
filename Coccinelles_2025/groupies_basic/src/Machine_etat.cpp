#include <Machine_etats.h>
#include <Arduino.h>
#include <cmath>

#include <define.h>

Machine_etats::Machine_etats(Asserv *p_asserv, Mesure_pos *p_mesure_pos, Irsensor *p_irsensor, Serv *p_servo)
{
    m_p_asserv = p_asserv;
    m_p_mesure_pos = p_mesure_pos;
    m_p_irsensor = p_irsensor;
    m_p_servo = p_servo;
}

void Machine_etats::setup()
{
    pinMode(4, INPUT);
    pinMode(EQUIPE, INPUT);
    etat = INIT;
    m_time = millis();
    m_time_global = millis();
    // Initialisation du capteur IR
    m_p_irsensor->setup();
    //m_p_servo->setup();

}

void Machine_etats::loop()
{

    if (millis() - m_time >= dt)
    {
        if (tirette == 1) {
            m_time_global = millis();
        }
        //Serial.print("millis = ");
        //Serial.println(millis());
        //Serial.print("m_time_global = ");
        //Serial.println(m_time_global);
        
        // Lire l'état de la tirette
        tirette = digitalRead(21);
        // Serial.print("tirette = ");
        // Serial.println(tirette);
        equipe = digitalRead(EQUIPE);
        // Serial.print("equipe = ");
        // Serial.println(equipe);

        // Utilisation du capteur IR pour la distance minimale
        m_p_irsensor->loop();
        m_minimum_distance = m_p_irsensor->ir_minimum_distance;
        //Serial.print("m_minimum_distance = ");
        //Serial.println(m_minimum_distance);
        Serial.print("tps écoulé :");
        Serial.println(millis()-m_time_global);

        switch (etat)
        {
        case INIT:
            if (millis() - m_time_global >= TIMEGLOBAL)
            {
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, angle);
            etat = END;
            }
            else {
            if (equipe == 1)
            {
                /*Coté gauche par rapport à scène*/
                pos_finit_x = GTURNX3;//NUMBER
                pos_finit_y = GTURNY3;//NUMBER
                turn_x = GTURNX3;//NUMBER
                turn_y = GTURNY3;//NUMBER
                fin_x = GFINX3;//NUMBER
                fin_y = GFINY3;//NUMBER
                fin_final_x = GFINX3;//NUMBER
                fin_final_y = GFINY3;//NUMBER
            }
            else
            {
                /*Coté droite par rapport à scène*/
                pos_finit_x = DTURNX3;//NUMBER
                pos_finit_y = DTURNY3;//NUMBER
                turn_x = DTURNX3;//NUMBER
                turn_y = DTURNY3;//NUMBER
                fin_x = DFINX3;//NUMBER
                fin_y = DFINY3;//NUMBER
                fin_final_x = DFINX3;//NUMBER
                fin_final_y = DFINY3;//NUMBER
            }
            // Serial.println("init");
            // Serial.print("tirette = ");
            // Serial.println(tirette);
            // Serial.println("move");
            // Serial.print("posex:");
            // Serial.println(pos_x);
            // Serial.print("poseY:");
            // Serial.println(pos_y);
            if ((millis() - m_time_global >= START_TIME3) && tirette == 0) // NUMBER
            {
                etat = MOVE;
            }
            else
            {
                etat = INIT;
            }
            }
            break;
        case MOVE:
            //Serial.print("tps écoulé :");
            //Serial.println(millis()-m_time_global);
            if (millis() - m_time_global >= TIMEGLOBAL)
            {
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, angle);
            etat = END;
            }
            else {

            // Serial.println("move");
            // Serial.print("posex:");
            // Serial.println(pos_x);
            // Serial.print("poseY:");
            // Serial.println(pos_y);
            // Serial.print("tetha:");
            // Serial.println(angle);
            if (m_minimum_distance <= DISTANCE_MIN)
            {
                etat = STOP;
            }
            else
            {
                // Serial.print("pos_finit_x = ");
                // Serial.println(pos_finit_x);
                // Serial.print("pos_finit_y = ");
                // Serial.println(pos_finit_y);
                pos_x = m_p_mesure_pos->position_x + pos_init_x;
                pos_y = m_p_mesure_pos->position_y + pos_init_y;
                // if(abs(angle - atan2(pos_finit_y - pos_y, pos_finit_x - pos_x) >= 1 )){
                // Serial.print("#######ATENTION#######");
                // Serial.print("angle = ");
                // Serial.println(angle);
                // Serial.print("pos_finit_x = ");
                // Serial.println(pos_finit_x);
                // Serial.print("pos_finit_y = ");
                // Serial.println(pos_finit_y);
                // Serial.print("pos_x = ");
                // Serial.println(pos_x);
                // Serial.print("pos_y = ");
                // Serial.println(pos_y);
                //}
                angle = atan2(pos_finit_y - pos_y, pos_finit_x - pos_x);
                // Serial.print("nouvel angle = ");
                // Serial.println(angle);
                // Serial.print("angle = ") ;
                // Serial.println(angle);
                m_p_asserv->asserv_global(SPEED, SPEED, angle); // corrige l'angle.

                condx_turn = (pos_x <= turn_x + EPSP) && (pos_x >= turn_x - EPSP);
                condy_turn = (pos_y <= turn_y + EPSP) && (pos_y >= turn_y - EPSP);

                if (condx_turn && condy_turn)
                {
                    Serial.println("TURNRNRNRNRNNRRNNRNRNRNRNNRNRNRNRNRNRNRNRNRNRRNNRNRNRNRNRN");
                    pos_finit_x = fin_x;
                    pos_finit_y = fin_y;
                    has_turned = true;
                    // m_p_mesure_pos->reinitialise() ;
                    etat = MOVE;
                }

                condx_arret = (pos_x <= fin_final_x + EPSP) && (pos_x >= fin_final_x - EPSP);
                condy_arret = (pos_y <= fin_final_y + EPSP) && (pos_y >= fin_final_y - EPSP);
                if (condx_arret && condy_arret && has_turned)
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
            if (millis() - m_time_global >= TIMEGLOBAL)
            {
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, angle);
            etat = END;
            }
            else
            {
                // Serial.println("stop");
                m_p_asserv->asserv_global(0, 0, m_p_mesure_pos->position_theta);
                if (m_minimum_distance > DISTANCE_MIN)
                {
                    etat = MOVE;
                }
                else
                {
                    etat = STOP;
                }
            }
            // Serial.println("stop");
            m_p_asserv->asserv_global(0, 0, m_p_mesure_pos->position_theta);
            if (m_minimum_distance > DISTANCE_MIN)
            {
                etat = MOVE;
            }
            else
            {
                etat = STOP;
            }
            break;

        case END:
            // Serial.println("end") ;
            m_p_asserv->asserv_global(0, 0, m_p_mesure_pos->position_theta);
            //m_p_servo->blink(TEMPS_BLINK, ANGLE1, ANGLE2) ;
            break;
        }
        m_time = millis();
    }
}