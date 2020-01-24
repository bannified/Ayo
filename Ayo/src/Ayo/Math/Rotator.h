#pragma once

#include "glm/fwd.hpp"

namespace Ayo
{
    struct Quaternion;
    struct Vector3;

    /**
     * Container for rotation information
     *
     * All values stored in terms of euler angles (in radians).
     */
    struct Rotator
    {
    public:
        /* Rotation about the right axis (x-axis), looking up and down, 0 = Straight ahead, +ve up, -ve down*/
        float Pitch;

        /* Rotation about up axis (y-axis), rotating left and right, 0 = east, +ve right, -ve left*/
        float Yaw;

        /* Rotation about the forward axis (z-axis), tilting your head, 0 = upright (eyes parallel to xz-plane), +ve Clockwise, -ve Counter-Clockwise*/
        float Roll;

    public:

        /* A rotator of zero degrees on each axis*/
        static const Rotator ZeroRotator;

    public:
        ~Rotator();
        Rotator();
        Rotator(float pitch, float yaw, float roll);
        Rotator(float value);

        Rotator(const glm::quat quaternion);

        /**
          * Get Rotation as a quaternion.
          *
          * @return Rotation as a quaternion.
         */
        Quaternion AsQuaternion() const;

        Vector3 TransformVectorNoScale(const Vector3& vec) const;

        Vector3 AsVector3() const;

    public:

        // Binary operator overloads (arithmetic)

        /**
         * Get the result of adding a rotator to this.
         *
         * @param R The other rotator.
         * @return The result of adding a rotator to this.
         */
        inline Rotator operator+(const Rotator& rot) const
        {
            return Rotator(Pitch + rot.Pitch, Yaw + rot.Yaw, Roll + rot.Roll);
        }

        /**
         * Get the result of subtracting a rotator from this.
         *
         * @param R The other rotator.
         * @return The result of subtracting a rotator from this.
         */
        inline Rotator operator-(const Rotator& rot) const
        {
            return Rotator(Pitch - rot.Pitch, Yaw - rot.Yaw, Roll - rot.Roll);
        }

        /**
         * Get the result of scaling this rotator.
         *
         * @param Scale The scaling factor.
         * @return The result of scaling.
         */
        inline Rotator operator*(float scale) const
        {
            return Rotator(Pitch * scale, Yaw * scale, Roll * scale);
        }

        // Binary comparison operators.

        /**
         * Checks whether two rotators are identical. This checks each component for exact equality.
         *
         * @param R The other rotator.
         * @return true if two rotators are identical, otherwise false.
         * @see Equals()
         */
        inline bool operator==(const Rotator& rot) const
        {
            return Roll == rot.Roll && Pitch == rot.Pitch && Yaw == rot.Yaw;
        }

        /**
         * Checks whether two rotators are different.
         *
         * @param V The other rotator.
         * @return true if two rotators are different, otherwise false.
         */
        inline bool operator!=(const Rotator& rot) const
        {
            return Roll != rot.Roll || Pitch != rot.Pitch || Yaw == rot.Yaw;
        }

        // Assignment operators.

        /**
         * Adds another rotator to this.
         *
         * @param R The other rotator.
         * @return Copy of rotator after addition.
         */
        inline Rotator operator+=(const Rotator& rot)
        {
            Roll = Roll + rot.Roll;
            Pitch = Pitch + rot.Pitch;
            Yaw = Yaw + rot.Yaw;
            return *this;
        }

        /**
         * Subtracts another rotator from this.
         *
         * @param R The other rotator.
         * @return Copy of rotator after subtraction.
         */
        inline Rotator operator-=(const Rotator& rot)
        {
            Roll = Roll - rot.Roll;
            Pitch = Pitch - rot.Pitch;
            Yaw = Yaw - rot.Yaw;
            return *this;
        }

        /**
         * Multiply this rotator by a scaling factor.
         *
         * @param Scale The scaling factor.
         * @return Copy of the rotator after scaling.
         */
        inline Rotator operator*=(float scale)
        {
            Roll = Roll * scale;
            Pitch = Pitch * scale;
            Yaw = Yaw * scale;
            return *this;
        }

    };
}
