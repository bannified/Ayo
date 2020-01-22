#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#define THRESH_VECTOR_NORMALIZED (0.01f)

namespace Ayo
{
    struct Vector3
    {
        friend struct Rotator;
        friend struct Quaternion;

    private:
        glm::vec3 m_Vector;

    public:
        Vector3();
        ~Vector3();

        /**
         * Constructor initializing all components to a single floating-point value.
         *
         * @param inFloat value to set all components to.
         */
        Vector3(float inFloat);

        /**
         * Constructor initializing each component to a value each.
         *
         * @param inX X coordinate value.
         * @param inY Y coordinate value.
         * @param inZ Z coordinate value.
         */
        Vector3(float inX, float inY, float inZ);

    private:
        Vector3(glm::vec3 vec);

    public:
        inline float GetX() const { return m_Vector.x; }
        inline float GetY() const { return m_Vector.y; }
        inline float GetZ() const { return m_Vector.z; }

    public:

        /** A zero vector (0,0,0) */
        static const Vector3 ZeroVector;

        /** One vector (1,1,1) */
        static const Vector3 OneVector;

        /** Unreal up vector (0,1,0) */
        static const Vector3 UpVector;

        /** Unreal down vector (0,-1,0) */
        static const Vector3 DownVector;

        /** Unreal forward vector (0,0,-1) */
        static const Vector3 ForwardVector;

        /** Unreal backward vector (0,0,1) */
        static const Vector3 BackwardVector;

        /** Unreal right vector (1,0,0) */
        static const Vector3 RightVector;

        /** Unreal left vector (-1,0,0) */
        static const Vector3 LeftVector;

        /* Common vector operations */

        /**
         * Checks whether vector is normalized.
         *
         * @return true if normalized, false otherwise.
         */
        bool IsNormalized() const;

        /**
         * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
         *
         */
        void Normalize();

        /**
         * Get the length (magnitude) of this vector.
         *
         * @return The length of this vector.
         */
        inline float Size() const;

        /**
         * Get the squared length of this vector.
         *
         * @return The squared length of this vector.
         */
        inline float SizeSquared() const;

        inline Vector3 CrossProduct(const Vector3& A, const Vector3& B)
        {
            return glm::cross(A.m_Vector, B.m_Vector);
        }

        inline float Vector3::DotProduct(const Vector3& A, const Vector3& B)
        {
            return glm::dot(A.m_Vector, B.m_Vector);
        }

        /**
         * Euclidean distance between two points.
         *
         * @param V1 The first point.
         * @param V2 The second point.
         * @return The distance between two points.
         */
        static inline float Dist(const Vector3 &V1, const Vector3 &V2) { return glm::distance(V1.m_Vector, V2.m_Vector); }
        static inline float Distance(const Vector3 &V1, const Vector3 &V2)
        {
            return Dist(V1, V2);
        }

        /**
         * Squared distance between two points.
         *
         * @param V1 The first point.
         * @param V2 The second point.
         * @return The squared distance between two points.
         */
        static FORCEINLINE float DistSquared(const Vector3 &V1, const Vector3 &V2) { return glm::distance2(V1.m_Vector, V2.m_Vector); }

        /**
         * Gets the result of component-wise addition of this by another vector.
         *
         * @param vec vector to add from this one.
         * @return The result of the component-wise vector addition
         */
        inline Vector3 operator+(const Vector3& vec) const { return { m_Vector + vec.m_Vector }; }

        /**
         * Gets the result of component-wise subtraction of this by another vector.
         *
         * @param vec vector to subtract from this one.
         * @return The result of the component-wise vector subtraction
         */
        inline Vector3 operator-(const Vector3& vec) const { return { m_Vector - vec.m_Vector }; }

        /**
         * Gets the result of scaling the vector (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        inline Vector3 operator*(float scale) const { return m_Vector * scale; }

        /**
         * Gets the result of dividing each component of the vector by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        inline Vector3 operator/(float scale) const { return m_Vector / scale; };

        /**
         * Gets the result of component-wise multiplication of this vector by another.
         *
         * @param vec The vector to multiply with.
         * @return The result of multiplication.
         */
        inline Vector3 operator*(const Vector3& vec) const { return m_Vector * vec.m_Vector; }

        /**
         * Gets the result of component-wise division of this vector by another.
         *
         * @param vec The vector to divide by.
         * @return The result of division.
         */
        inline Vector3 operator/(const Vector3& vec) const { return m_Vector / vec.m_Vector; };

        // Binary comparison operators.

        /**
         * Check against another vector for equality.
         *
         * @param vec The vector to check against.
         * @return true if the vectors are equal, false otherwise.
         */
        inline bool operator==(const Vector3& vec) const { return m_Vector == vec.m_Vector; };

        /**
         * Check against another vector for inequality.
         *
         * @param vec The vector to check against.
         * @return true if the vectors are not equal, false otherwise.
         */
        inline bool operator!=(const Vector3& vec) const { return m_Vector != vec.m_Vector; };

        /**
         * Get a negated copy of the vector.
         *
         * @return A negated copy of the vector.
         */
        inline Vector3 operator-() const { return -m_Vector;}

        /**
         * Adds another vector to this.
         * Uses component-wise addition.
         *
         * @param V Vector to add to this.
         * @return Copy of the vector after addition.
         */
        inline Vector3 operator+=(const Vector3& vec) { return m_Vector += vec.m_Vector; }

        /**
         * Subtracts another vector from this.
         * Uses component-wise subtraction.
         *
         * @param V Vector to subtract from this.
         * @return Copy of the vector after subtraction.
         */
        inline Vector3 operator-=(const Vector3& vec) { return m_Vector -= vec.m_Vector; }

        /**
         * Scales the vector.
         *
         * @param Scale Amount to scale this vector by.
         * @return Copy of the vector after scaling.
         */
        inline Vector3 operator*=(float scale) { return m_Vector *= scale; }

        /**
         * Divides the vector by a number.
         *
         * @param V What to divide this vector by.
         * @return Copy of the vector after division.
         */
        inline Vector3 operator/=(float scale) { return m_Vector /= scale; }
    };
}



