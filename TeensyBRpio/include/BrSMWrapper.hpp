#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "BrSM.hpp"
// wrapper to manage the state machines



class BrSMWrapper : public BrSM
{
public :
    BrSMWrapper();

    void sendEvent();

    int test;
};

#endif  // STATE_MACHINE_H