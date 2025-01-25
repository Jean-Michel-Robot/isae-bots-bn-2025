#ifndef _TRAJECTORY_HPP_
#define _TRAJECTORY_HPP_

#include "defines/math.hpp"
#include "geometry/Position2D.hpp"

#include <optional>

/**
 * A continuous (reasonably smooth, i.e. at least of class C2) 2D-trajectory the robot is expected to follow.
 *
 * The trajectory is described by the successive positions of a point that moves along the trajectory.
 * This point can be seen as the target position for the robot.
 *
 * When the `Trajectory` instance is created, this point must be at the beginning of the trajectory.
 * The implementation is responsible for keeping track of this point internally as it advances.
 *
 * If the trajectory has tight curves, the robot may not be able to follow it in an accurate way. The controller and this
 * class might be extended later to implement automatic braking before curves.
 *
 * This class must be inherited.
 */
class Trajectory {
  public:
    /**
     * Advances the current position on the trajectory by the given distance.
     * @param distance The distance (in meters) between the current trajectory position and the new position. If the new position would fall
     * outside the trajectory, then the position should be advanced to the end of the trajectory instead.
     * @return true if the position was advanced. false if the position is already at the end of the trajectory. If this method returns false,
     * subsequent calls to advance() must also return false.
     *
     * If `distance < 0`, the behavior is undefined.
     */
    virtual bool advance(double_t distance) = 0;

    /**
     * Returns the current position on the trajectory. The position must be heading forward in the current local direction of the trajectory.
     * After advance() has returned false, this must return the last point of the trajectory.
     */
    virtual Position2D<Meter> getCurrentPosition() const = 0;

    /**
     * Returns the distance between the current position and the end of the trajectory. This allows to implement a deceleration ramp to stop the robot
     * as close to the end of the trajectory as possible (without overshoot and ringing).
     *
     * - 0 means the current position has reached the end of the trajectory. It is a logic error to return 0 unless advance() would return false.
     * - An empty optional means the trajectory is inifite or the remaining distance cannot be determined.
     * - Negative values are illegal and will lead to unspecified behaviour.
     *
     * After advance() has returned false, this must return 0.
     */
    virtual std::optional<double_t> getRemainingDistance() const = 0;

    /**
     * Returns the maximum absolute curvature of the trajectory for the next `distance` meters, starting at the current position.
     * The curvature is used to anticipate deceleration in turns.
     *
     * - Returning 0 means the trajectory is a straight line and effectively disables turn anticipation.
     *   0 is also a valid default value for trajectories that do not support curvature estimation.
     * - Returning a negative value is illegal and unspecified behavior.
     *
     * If `distance < 0`, the behavior is undefined.
     */
    virtual double_t getMaxCurvature(double_t distance) const = 0;

    /**
     * Attempts to recompute the trajectory such that:
     * - The new start position is `newStartPosition`. The initial direction of the trajectory is not required to match the robot's orientation.
     * - The current position is reset to the beginning of the trajectory.
     * - The recomputed trajectory eventually catches up with the remaining part of the initial trajectory (what this exactly means depends on the
     * trajectory). If the initially trajectory is finite, this usually means the recomputed trajectory is finite as well and has the same final
     * position.
     *
     * @returns true if the trajectory was successfully recomputed, false otherwise. If this returns false, the state of this object must not have
     * changed.
     *
     * The default implementation always returns false.
     *
     */
    virtual bool recompute(Position2D<Meter> newStartPosition) { return false; }

  protected:
    Trajectory() = default;
};

#endif