#include "controller/states/StateStandStill.hpp"
#include "logging.hpp"

namespace controller {

StateStandStill::StateStandStill(Position2D<Meter> restPosition, bool advertize) : m_restPosition(restPosition) {
    if (advertize) {
        log(INFO, "Entering controller state: Ready (standing still)");
    }
}

ControllerStatus StateStandStill::getStatus() const {
    return ControllerStatus::Still;
}

StateUpdateResult StateStandStill::update(double_t interval) {
    return PositionControl(m_restPosition);
}

} // namespace controller
