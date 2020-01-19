#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Ayo
{
    /**
     * Container for rotation information
     *
     * All values stored in terms of degrees (euler angles).
     */
    struct Rotator
    {
    public:
        /* Rotation about the forward axis (z-axis), tilting your head, 0 = upright (eyes parallel to xz-plane), +ve Clockwise, -ve Counter-Clockwise*/
        float Roll;

        /* Rotation about the right axis (x-axis), looking up and down, 0 = Straight ahead, +ve up, -ve down*/
        float Pitch;

        /* Rotation about up axis (y-axis), rotating left and right, 0 = east, +ve right, -ve left*/
        float Yaw;

    public:

        /* A rotator of zero degrees on each axis*/
        static const Rotator ZeroRotator;

    public:
        ~Rotator();
        Rotator();
        Rotator(float roll, float pitch, float yaw);

        explicit Rotator(const glm::quat quaternion);

    };
}
