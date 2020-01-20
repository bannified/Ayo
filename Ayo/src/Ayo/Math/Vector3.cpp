#include "ayopch.h"
#include "Vector3.h"

Ayo::Vector3::Vector3() : m_Vector(glm::vec3()) { }

const Ayo::Vector3 Ayo::Vector3::ZeroVector(0.0f, 0.0f, 0.0f);
const Ayo::Vector3 Ayo::Vector3::OneVector(1.0f, 1.0f, 1.0f);
const Ayo::Vector3 Ayo::Vector3::UpVector(0.0f, 1.0f, 0.0f);
const Ayo::Vector3 Ayo::Vector3::DownVector(0.0f, -1.0f, 0.0f);
const Ayo::Vector3 Ayo::Vector3::ForwardVector(0.0f, 0.0f, -1.0f);
const Ayo::Vector3 Ayo::Vector3::BackwardVector(0.0f, 0.0f, 1.0f);
const Ayo::Vector3 Ayo::Vector3::RightVector(1.0f, 0.0f, 0.0f);
const Ayo::Vector3 Ayo::Vector3::LeftVector(-1.0f, 0.0f, 0.0f);

bool Ayo::Vector3::IsNormalized() const
{
    return std::abs(1.0f - SizeSquared()) < THRESH_VECTOR_NORMALIZED;
}

void Ayo::Vector3::Normalize()
{
    glm::normalize(m_Vector);
}

float Ayo::Vector3::Size() const
{
    return glm::length(m_Vector);
}

float Ayo::Vector3::SizeSquared() const
{
    return glm::length2(m_Vector);
}

Ayo::Vector3::Vector3(glm::vec3 vec) : m_Vector(vec) { }

Ayo::Vector3::~Vector3() { }

Ayo::Vector3::Vector3(float inFloat) : m_Vector(glm::vec3(inFloat)) { }

Ayo::Vector3::Vector3(float inX, float inY, float inZ) : m_Vector(glm::vec3(inX, inY, inZ)) { }
