#include "ayopch.h"
#include "glm/gtx/euler_angles.hpp"

#include "SceneComponent.h"

#include "Ayo/Math/Quaternion.h"
#include "Ayo/Math/Vector3.h"
#include "Ayo/Math/Rotator.h"

Ayo::SceneComponent::SceneComponent()
{
    m_LocalLocation = Vector3(0.0f);
    m_LocalRotation = Rotator(0.0f);
    m_LocalScale = Vector3(1.0f);
}

Ayo::SceneComponent::~SceneComponent() = default;

void Ayo::SceneComponent::SetLocalLocation(Vector3 NewLocation)
{
    m_LocalLocation = NewLocation;
}

void Ayo::SceneComponent::AddLocalLocation(Vector3 deltaLocation)
{
    m_LocalLocation = m_LocalLocation + deltaLocation;
}

void Ayo::SceneComponent::SetLocalRotation(Rotator newRotation)
{
    m_LocalRotation = newRotation;
}

void Ayo::SceneComponent::AddLocalRotation(Rotator deltaRotation)
{
    const Quaternion currentQuat = m_LocalRotation.AsQuaternion().GetNormalized();
    const Quaternion targetQuat = currentQuat * deltaRotation.AsQuaternion();

    m_LocalRotation = targetQuat.AsRotator();
    
    // Correct, but suffers from gimbal lock and floating point errors for large numbers
    //m_LocalRotation += deltaRotation;
}

//Ayo::Rotator Ayo::SceneComponent::GetWorldRotation() const
//{
//
//}

//void Ayo::SceneComponent::SetWorldRotation(Rotator NewRotation)
//{
//
//}

void Ayo::SceneComponent::SetLocalScale(Vector3 newScale)
{
    m_LocalScale = newScale;
}

void Ayo::SceneComponent::AddLocalScale(Vector3 deltaScale)
{
    m_LocalScale += deltaScale;
}

//Ayo::Vector3 Ayo::SceneComponent::GetWorldScale() const
//{
//
//}

//void Ayo::SceneComponent::SetWorldScale(Vector3 NewScale)
//{
//
//}

void Ayo::SceneComponent::AddLocalOffset(Vector3 offset)
{
    const Quaternion currentQuat = m_LocalRotation.AsQuaternion().GetNormalized();
    const Vector3 DeltaOffset = currentQuat.RotateVector(offset);

    m_LocalLocation += DeltaOffset;
}

Ayo::Vector3 Ayo::SceneComponent::GetForwardVector() const
{
    return m_LocalRotation.TransformVectorNoScale(Vector3(0.0f, 0.0f, -1.0f));
}

Ayo::Vector3 Ayo::SceneComponent::GetUpVector() const
{
    return m_LocalRotation.TransformVectorNoScale(Vector3(0.0f, 1.0f, 0.0f));
}

Ayo::Vector3 Ayo::SceneComponent::GetRightVector() const
{
    return m_LocalRotation.TransformVectorNoScale(Vector3(1.0f, 0.0f, 0.0f));
}

glm::mat4 Ayo::SceneComponent::GetRelativeTransform()
{
    glm::mat4 res = glm::mat4(1.0f);

    res = glm::translate(res, m_LocalLocation.Get());

    res = res * glm::eulerAngleXYZ(m_LocalRotation.Pitch, m_LocalRotation.Yaw, m_LocalRotation.Roll);

    res = glm::scale(res, m_LocalScale.Get());

    return res;
}

