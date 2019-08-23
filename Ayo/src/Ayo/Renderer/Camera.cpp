#include "ayopch.h"
#include "Camera.h"

namespace Ayo
{

	Camera::Camera()
	{
		SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f));
		SetViewMatrix(glm::identity<glm::mat4>());
	}


	Camera::~Camera()
	{
	}

	void Camera::SetProjectionMatrix(glm::mat4 matrix)
	{
		m_ProjectionMatrix = matrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetViewMatrix(glm::mat4 matrix)
	{
		m_ViewMatrix = matrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
