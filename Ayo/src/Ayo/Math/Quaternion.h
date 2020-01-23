#pragma once

#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Ayo/Math/Rotator.h"

namespace Ayo
{
    struct Rotator;
    struct Vector3;

    /** For a 3D game engine, we're only interesting in using Quaternions to represent 3D rotations.
     * Therefore, we only have to use unit-length quaternions, obeying the constraint: x^2 + y^2 + z^2 + w^2 = 1
     * For now, it uses glm's quat internally.
     */
    struct Quaternion
    {
        friend struct Rotator;

    private:
        glm::quat m_Quaternion;

    public:
        /* Identity Quaternion */
        static const Quaternion Identity;

        inline Quaternion() { }
        ~Quaternion();

        inline glm::quat GetQuaternion() const { return m_Quaternion; }

        inline glm::quat GetInverse() const { return glm::inverse(m_Quaternion); }

        inline glm::quat GetNormalized() const { return glm::normalize(m_Quaternion); }

        /**
         * Per-component Constructor.
         *
         * @param InX X component of the quaternion
         * @param InY Y component of the quaternion
         * @param InZ Z component of the quaternion
         * @param InW W component of the quaternion
         */
        explicit inline Quaternion(float x, float y, float z, float w) 
            : m_Quaternion(glm::quat(x, y, z, w)) { }

        /**
         * Creates and initializes a new quaternion from the given rotator.
         *
         * @param R The rotator to initialize from.
         */
        explicit Quaternion(const glm::quat quaternion);

        /**
         * Creates and initializes a new quaternion from the given rotator.
         *
         * @param R The rotator to initialize from.
         */
        Quaternion(const Rotator& rot);

        /**
         * Creates and initializes a new quaternion from the a rotation around the given axis.
         *
         * @param Axis assumed to be a normalized vector
         * @param Angle angle to rotate above the given axis (in radians)
         */
        Quaternion(Vector3 Axis, float angleRad);


        /* Operator overloads */

        inline Quaternion operator*(const Quaternion& qua) const
        {
            Quaternion result = Quaternion(glm::cross(m_Quaternion, qua.m_Quaternion));
            return result;
        }

        /* Methods */

        inline Rotator AsRotator() const
        {
            const glm::quat normalized = glm::normalize(m_Quaternion);
            return Rotator(normalized);
        }
    };
}

