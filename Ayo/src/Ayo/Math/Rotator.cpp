#include "ayopch.h"
#include "Rotator.h"

const Ayo::Rotator Ayo::Rotator::ZeroRotator(0.0f, 0.0f, 0.0f);

Ayo::Rotator::~Rotator()
{

}

Ayo::Rotator::Rotator(float roll, float pitch, float yaw) 
    : Roll(roll), Pitch(pitch), Yaw(yaw) { }

Ayo::Rotator::Rotator(const glm::quat quaternion)
{
    // todo
}

Ayo::Rotator::Rotator() { }

