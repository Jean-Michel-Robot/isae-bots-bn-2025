#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

// -- SERVO POSITIONS --

// Clamp 1
#define CLAMP_2_1_OPEN_POS 5   // TODO 10
#define CLAMP_2_1_CLOSED_POS 170  // TODO 160

// Clamp 2 -> burned 
#define CLAMP_2_2_OPEN_POS 0   // TODO 10
#define CLAMP_2_2_CLOSED_POS 0  // TODO 160

// Clamp haut gauche
#define CLAMP_1_1_OPEN_POS 10  // TODO  5
#define CLAMP_1_1_CLOSED_POS 160  // TODO  170

// Clamp haut droite
#define CLAMP_1_2_OPEN_POS 5  // TODO  0
#define CLAMP_1_2_CLOSED_POS 170  // TODO 0

// The servo that opens first when deploying the banner
#define BANNER_1_DEPLOYED_POS 110  // TODO
#define BANNER_1_RETRACTED_POS 0  // TODO

// The other servo of the banner
#define BANNER_2_DEPLOYED_POS 110  // TODO
#define BANNER_2_RETRACTED_POS 0  // TODO

// -- STEPPERS CONFIGURATION (ELEVATORS) --

#define ELEVATOR_1_STEP_PER_REV 200 // TODO
#define ELEVATOR_2_STEP_PER_REV ELEVATOR_1_STEP_PER_REV // TODO

#define ELEVATOR_1_SPEED 1500 // rev per minute // TODO
#define ELEVATOR_2_SPEED ELEVATOR_1_SPEED // rev per minute // TODO

// number of steps between states DOWN and UP - change sign to invert direction
#define ELEVATOR_1_POS_OFFSET 12000 // TODO butée 43000    BAS
#define ELEVATOR_2_POS_OFFSET 12000 // TODO HAUT

// -- PINS --

#define ELEVATOR_1_STEP_PIN 3
#define ELEVATOR_1_DIR_PIN 4

#define ELEVATOR_2_STEP_PIN 5
#define ELEVATOR_2_DIR_PIN 6

#define CLAMP_1_1_PIN 22 //20
#define CLAMP_1_2_PIN 23  //21
#define CLAMP_2_1_PIN 20 //22
#define CLAMP_2_2_PIN 21 // 23

#define BANNER_1_PIN 9
#define BANNER_2_PIN 10

#define BUMPER_1_PIN 11 // TODO
#define BUMPER_2_PIN 12 // TODO

// -- OTHER CONFIG --

#define CALLBACK_INTERVAL 10  // ms
#define BANNER_INTERVAL 1000    // ms // TODO

// If moving the elevator takes more time than the timeout, `ElevatorStepper::loop` returns anyway after (roughly) the timeout, so ROS orders can
// still be processed and other actuators' state can be updated.
// The displacement continues the next time `ElevatorStepper::loop` is called.
#define STEPPER_YIELD_TIMEOUT 50 // ms

#endif