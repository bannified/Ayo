#include "ayopch.h"
#include "Rotator.h"

const Ayo::Rotator Ayo::Rotator::ZeroRotator(0.0f, 0.0f, 0.0f);

Ayo::Rotator::~Rotator()
{

}

Ayo::Rotator::Rotator(float roll, float pitch, float yaw) 
    : Roll(roll), Pitch(pitch), Yaw(yaw) { }

Ayo::Rotator::Rotator(float value)
    : Roll(value), Pitch(value), Yaw(value) { }

Ayo::Rotator::Rotator(const glm::quat quaternion)
{
    // todo
}

Ayo::Rotator::Rotator() 
    : Roll(0), Pitch(0), Yaw(0) { }

