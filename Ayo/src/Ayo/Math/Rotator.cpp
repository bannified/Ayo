#include "ayopch.h"
#include "Rotator.h"

const Ayo::Rotator Ayo::Rotator::ZeroRotator(0.0f, 0.0f, 0.0f);

Ayo::Rotator::~Rotator()
{

}

Ayo::Rotator::Rotator(float roll, float pitch, float yaw) 
    : Pitch(pitch), Yaw(yaw), Roll(roll) { }

Ayo::Rotator::Rotator(float value)
    :  Pitch(value), Yaw(value), Roll(value) { }

Ayo::Rotator::Rotator(const glm::quat quaternion)
{
    // todo
}

Ayo::Rotator::Rotator() 
    : Pitch(0), Yaw(0), Roll(0) { }

