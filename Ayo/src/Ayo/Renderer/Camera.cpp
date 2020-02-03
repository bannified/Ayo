#include "ayopch.h"
#include "Camera.h"

namespace Ayo
{

	Camera::Camera()
	{
		SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f));
		RecalculateViewProjectionMatrix();
	}


	Camera::~Camera()
	{
	}

	void Camera::SetProjectionMatrix(glm::mat4 matrix)
	{
		m_ProjectionMatrix = matrix;
	}

	void Camera::RecalculateViewProjectionMatrix()
	{
        glm::mat4 transform = GetRelativeTransform();
        // todo: View Projection affects scale of the world since we're using GetRelativeTransform(), which SHOULD NOT happen.
		m_ViewProjectionMatrix = m_ProjectionMatrix * glm::inverse(transform);
	}

}
