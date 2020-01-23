#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Ayo/Components/SceneComponent.h"

namespace Ayo {

	class Camera : public SceneComponent
	{
	public:
		Camera();
		~Camera();

		inline glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjectionMatrix(glm::mat4 matrix);
		void SetViewMatrix(glm::mat4 matrix);

		inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::quat GetOrientation() const { return m_Orientation; }

		void SetPosition(const glm::vec3& pos);

		void SetOrientation(const glm::quat& orient);

		inline void Rotate(float eulerAngle, const glm::vec3& axis)
		{
			m_Orientation *= glm::angleAxis(eulerAngle, axis * m_Orientation);
			m_Rotation += eulerAngle;
			RecalculateViewProjectionMatrix();
		}

		inline glm::vec3 GetUpVector() const { return glm::vec3(0.0f, 1.0f, 0.0f); } // todo: move into a Vector3D class
		inline glm::vec3 GetForwardVector() const { return glm::vec3(0.0f, 0.0f, -1.0f); } // todo: move into a Vector3D class
		inline glm::vec3 GetRightVector() const { return glm::vec3(1.0f, 0.0f, 0.0f); } // todo: move into a Vector3D class



	private:
		void RecalculateViewProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ViewProjectionMatrix; // cached value

		// TO-DO: Refactor to a Transform class.
		glm::mat4 m_Transform = glm::mat4(1.0f);
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::quat m_Orientation;

		float m_Rotation = 0.0f;
	};

}

