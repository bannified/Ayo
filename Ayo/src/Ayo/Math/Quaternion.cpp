#include "ayopch.h"
#include "Quaternion.h"

#include "Vector3.h"
#include "Rotator.h"

const Ayo::Quaternion Ayo::Quaternion::Identity = Quaternion(0,0,0,1);

Ayo::Quaternion::~Quaternion()
{

}

Ayo::Quaternion::Quaternion(const glm::quat quaternion) 
    : m_Quaternion(quaternion) { }

Ayo::Quaternion::Quaternion(const Rotator& rot)
    : m_Quaternion(rot.AsQuaternion().m_Quaternion) { }

Ayo::Quaternion::Quaternion(Vector3 Axis, float angleRad)
    : m_Quaternion(glm::angleAxis(angleRad, Axis.m_Vector)) { }
