#ifndef _SPEC_MANAGER_HPP_
#define _SPEC_MANAGER_HPP_

#include "specializations/actuators.hpp"
#include "specializations/clock.hpp"
#include "specializations/controller.hpp"
#include "specializations/feedback.hpp"

#include "manager/ControllerManager.hpp"

using manager_t = manager::ControllerManager<actuators_t, controller_t, feedback_t, _clock_t>;

#if !defined(ARDUINO) && defined(_SIMULATION)
/// Convenience method to create the manager
inline manager_t createManager(Position2D<Meter> initialPosition = {}) {
    feedback_t feedback;
    feedback.resetPosition(initialPosition);
    actuators_t motors = feedback.createMotorStub();
    return manager_t(std::move(motors), std::move(feedback));
}
#endif

#endif