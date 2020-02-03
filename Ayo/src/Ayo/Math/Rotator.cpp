#include "ayopch.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Vector3.h"
#include "Rotator.h"
#include "Quaternion.h"

const Ayo::Rotator Ayo::Rotator::ZeroRotator(0.0f, 0.0f, 0.0f);

Ayo::Rotator::~Rotator()
{

}

Ayo::Rotator::Rotator(float pitch, float yaw, float roll) 
    : Pitch(pitch), Yaw(yaw), Roll(roll) { }

Ayo::Rotator::Rotator(float value)
    :  Pitch(value), Yaw(value), Roll(value) { }

Ayo::Rotator::Rotator(const glm::quat quaternion) 
    : Pitch(glm::pitch(quaternion)), Yaw(glm::yaw(quaternion)), Roll(glm::roll(quaternion)) { }

Ayo::Rotator::Rotator() 
    : Pitch(0), Yaw(0), Roll(0) { }

Ayo::Quaternion Ayo::Rotator::AsQuaternion() const
{
    return Ayo::Quaternion(glm::quat(glm::vec3(Pitch, Yaw, Roll)));
}

Ayo::Vector3 Ayo::Rotator::TransformVectorNoScale(const Vector3& vec) const
{
    return glm::rotate(AsQuaternion().m_Quaternion, vec.m_Vector);
}

Ayo::Vector3 Ayo::Rotator::AsVector3Radians() const
{
    return Ayo::Vector3(glm::vec3(Pitch, Yaw, Roll));
}

Ayo::Vector3 Ayo::Rotator::AsVector3Degrees() const
{
    return Ayo::Vector3(glm::vec3(glm::degrees(Pitch), glm::degrees(Yaw), glm::degrees(Roll)));
}

Ayo::Rotator Ayo::Rotator::FromDegrees(const glm::vec3 angleDegrees)
{
    return FromDegrees(angleDegrees.x, angleDegrees.y, angleDegrees.z);
}

Ayo::Rotator Ayo::Rotator::FromDegrees(const float pitchDegree, const float yawDegree, const float rollDegree)
{
    return Rotator(glm::radians(pitchDegree), glm::radians(yawDegree), glm::radians(rollDegree));
}
