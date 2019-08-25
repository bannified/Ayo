#include "ayopch.h"
#include "Camera.h"

namespace Ayo
{

	Camera::Camera()
	{
		SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f));
		SetViewMatrix(glm::identity<glm::mat4>());
		m_Orientation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		RecalculateViewProjectionMatrix();
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
	}

	void Camera::SetPosition(const glm::vec3& pos)
	{
		m_Position = pos;
		RecalculateViewProjectionMatrix();
	}

	void Camera::SetOrientation(const glm::quat& orient)
	{
		m_Orientation = orient;
		RecalculateViewProjectionMatrix();
	}

	void Camera::RecalculateViewProjectionMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4_cast(m_Orientation), m_Position);
			//glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
			//glm::translate(glm::mat4_cast(m_Orientation), m_Position);

		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
