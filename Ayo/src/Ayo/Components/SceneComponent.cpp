#include "ayopch.h"
#include "SceneComponent.h"

#include "Ayo/Math/Quaternion.h"
#include "Ayo/Math/Vector3.h"
#include "Ayo/Math/Rotator.h"

Ayo::SceneComponent::SceneComponent()
{

}

Ayo::SceneComponent::~SceneComponent()
{

}

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
    const Quaternion currentQuat = m_LocalRotation.AsQuaternion();
    const Quaternion targetQuat = currentQuat * deltaRotation.AsQuaternion();

    m_LocalRotation = Rotator(targetQuat.GetQuaternion());
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
    m_LocalLocation = offset * GetRightVector();
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

