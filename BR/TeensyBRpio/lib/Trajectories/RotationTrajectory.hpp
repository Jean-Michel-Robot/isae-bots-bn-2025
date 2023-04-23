#ifndef H_ROTATION_TRAJECTORY
#define H_ROTATION_TRAJECTORY

#include <Trajectory.hpp>

class RotationTrajectory : public Trajectory
{
public :

    RotationTrajectory(float initialGoalSpeed, float initialAccelParam);
    // TODO destructeur

    void setDest(OrderType order) override;

private:

    // variables caractéristiques de la trajectoire
    // pour le déplacement linéaire c'est juste la position de fin
    float thetaDest;

    bool detectEndRamp() override;
    void updateTrajectoryState() override;
    
};


#endif