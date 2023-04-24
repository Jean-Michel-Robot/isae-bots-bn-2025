
#include "Asserv.hpp"

#include "OdosPosition.hpp"
#include <Motors.hpp>

#include "ROS.hpp"
#include "main_loop.hpp"

#include <cmath>




Asserv::Asserv(float k1, float k2, float k3) {
    m_k1 = k1;
    m_k2 = k2;
    m_k3 = k3;

    setErrorPositionThreshold(OBJECTIVE_THRESHOLD_X, OBJECTIVE_THRESHOLD_Y, OBJECTIVE_THRESHOLD_THETA);

    m_state = ACTIVE;
}

void Asserv::updateError(Position2D trajectoryPointPos) {

    Position2D currentBotPosition = p_odos->getRobotPosition();
    Position2D errorPosTableFrame = trajectoryPointPos - p_odos->getRobotPosition();
    float angle = currentBotPosition.theta;

    //TOTEST CHECK IF REF CHANGE IS OK (avec alpha et beta aussi)
    m_errorPos.x = cos(angle)*errorPosTableFrame.x + sin(angle)*errorPosTableFrame.y;
    m_errorPos.y = -sin(angle)*errorPosTableFrame.x + cos(angle)*errorPosTableFrame.y;
    m_errorPos.theta = errorPosTableFrame.theta;
}



void Asserv::updateCommand(float vd, float omega_d) {

    // update trajectory
    // p_linearTrajectory->updateTrajectory( micros() );

    //FORTEST
    sendMotorCommand(0, vd); // RIGHT MOTOR
    sendMotorCommand(1, vd); // LEFT MOTOR

    return;

    if(m_state == ACTIVE) {
        
        // get trajectory speed (linear and angular)
        // m_target[0] = p_linearTrajectory->getTrajectoryLinearSpeed();
        // m_target[1] = p_linearTrajectory->getTrajectoryAngularSpeed();

        // float vd = m_target[0];
        // float omega_d = m_target[1];

        // // update error using trajectory
        // this->updateError();

        /* En utilisant la formule qu'on sait pas d'où elle sort*/
        if(cos(m_errorPos.theta) == 0){
            // Protection div par 0 (ça peut servir)
            m_botSpeed[0] = 0;
            m_botSpeed[1] = 0;
        }
        else {   
            m_botSpeed[0] = (vd - m_k1*abs(vd)*(m_errorPos.x + m_errorPos.y*tan(m_errorPos.theta)))/cos(m_errorPos.theta);
            m_botSpeed[1] = omega_d - (m_k2*vd*m_errorPos.y  + m_k3*abs(vd)*tan(m_errorPos.theta))*pow(cos(m_errorPos.theta),2);
        }

        m_leftWheelSpeed = m_botSpeed[0] + m_botSpeed[1]*WHEEL_DISTANCE/2; 
        m_rightWheelSpeed = m_botSpeed[0] - m_botSpeed[1]*WHEEL_DISTANCE/2;

        // send the commands to the motors
        sendMotorCommand(0, m_leftWheelSpeed);
        // sendMotorCommand(1, m_rightWheelSpeed);
    }

    else {
        //TODO : make the axis states IDLE
    }
}

void Asserv::setErrorPositionThreshold(float x, float y, float theta){
    if (x>0)
        m_errorPosThreshold.x = x;
    
    if (y>0)
        m_errorPosThreshold.y = y;

    if (theta>0)
        m_errorPosThreshold.theta = theta;
}


bool Asserv::isAtObjectivePoint(bool checkAngle){
    
    // this->updateError();

    if (abs(m_errorPos.x) > m_errorPosThreshold.x)
        return false;
    else if (abs(m_errorPos.y) > m_errorPosThreshold.y)
        return false;
    else if (checkAngle && (abs(fmod(m_errorPos.theta, TWO_PI)) > m_errorPosThreshold.theta))
        return false;
    else
        return true;
}

void Asserv::loop() {
    // this->updateCommand();

    /*
    Dans l'ordre :

    setRobotPos(x0, y0, theta0);
    setDest( <vars> );

    beginTrajectory(t0);

    updateTrajectory(t);

    getTrajectoryPoint() -> (x, y, theta)
    getTrajectoryLinearSpeed() -> V
    getTrajectoryAngularSpeed() -> omega
    */
}

