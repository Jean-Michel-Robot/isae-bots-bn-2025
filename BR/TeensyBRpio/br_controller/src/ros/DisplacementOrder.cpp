#include "ros/DisplacementOrder.hpp"
#include "logging.hpp"
#include "rotations/SetHeadingProfile.hpp"
#include "trajectories/BezierTrajectory.hpp"
#include "trajectories/LinearTrajectory.hpp"

DisplacementOrder::DisplacementOrder(GoalType type, Position2D<Millimeter> goalPosition) : type(type), position(goalPosition) {}

DisplacementOrder::DisplacementOrder(int type, Position2D<Millimeter> goalPosition) : DisplacementOrder(UNVALID_GOALTYPE, goalPosition) {
    switch (type) {
        case LINEAR_FINAL:
        case LINEAR_TRANS:
        case ORIENTATION:
        case LINEAR_REVERSE:
        case STOP:
        case RESET:
        case CONTROL:
        case TEST_BEZIER:
            this->type = (GoalType)type;
            break;
        default:
            log(WARN, "Order ignored because not recognized: " + std::to_string(type));
            break;
    }
}

template <Actuators TActuators, PositionFeedback TFeedback, Clock TClock>
void DisplacementOrder::operator()(manager_t<TActuators, TFeedback, TClock> &manager) const {
    switch (type) {
        case LINEAR_FINAL:
            goTo(manager, FORWARD, position, position.theta);
            break;
        case LINEAR_TRANS:
            goTo(manager, FORWARD, position, {});
            break;
        case LINEAR_REVERSE:
            goTo(manager, REVERSE, position, {});
            break;
        case ORIENTATION:
            manager.sendOrder([&](controller_t &controller, Position2D<Meter> robotPosition) {
                controller.template startRotation<SetHeadingProfile>(robotPosition.theta, position.theta);
            });
            break;
        case STOP:
            manager.sendOrder([&](controller_t &controller, Position2D<Meter> robotPosition) { controller.brakeToStop(); });
            break;
        case RESET:
            manager.resetPosition(position);
            break;
        case CONTROL: {
            Vector2D<Millimeter> speedFactor = position / CONTROL_MAX_SPEED;
            manager.sendOrder([&](controller_t &controller, Position2D<Meter> robotPosition) {
                controller.setSetpointSpeed({speedFactor.x * controller.getMaxSpeeds().linear, speedFactor.y * controller.getMaxSpeeds().angular})
                    /*, enforceMaxSpeeds = true */;
            });
            break;
        }
        case TEST_BEZIER: {
            manager.sendOrder([&](controller_t &controller, Position2D<Meter> robotPosition) {
                controller.template startTrajectory<BezierTrajectory, std::vector<Point2D<Meter>>>(
                    FORWARD, {{0,0}, {2.8, 0.7}, {0, 1.8}, {1.3, 1.8}}, std::nullopt);
            });
            break;
        } break;
        default:
            break;
    }
}

template <Actuators TActuators, PositionFeedback TFeedback, Clock TClock>
void DisplacementOrder::goTo(manager_t<TActuators, TFeedback, TClock> &manager, DisplacementKind kind, Vector2D<Millimeter> goalPosition,
                             std::optional<Angle> angle) {
    manager.sendOrder([&](controller_t &controller, Position2D<Meter> robotPosition) {
        controller.template startTrajectory<LinearTrajectory, Point2D<Meter>, Point2D<Meter>>(kind, (Point2D<Meter>)robotPosition,
                                                                                              (Point2D<Meter>)goalPosition.toMeters(), angle);
    });
}

#include "specializations/manager.hpp"
template void DisplacementOrder::operator()<actuators_t, feedback_t, _clock_t>(::manager_t &manager) const;