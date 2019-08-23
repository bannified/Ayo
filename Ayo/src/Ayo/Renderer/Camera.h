#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Ayo {

	class Camera
	{
	public:
		Camera();
		~Camera();

		inline glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjectionMatrix(glm::mat4 matrix);
		void SetViewMatrix(glm::mat4 matrix);

		inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

		inline glm::vec3 GetLocation() const { return m_Location; }
		inline glm::quat GetRotation() const { return m_Rotation; }

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ViewProjectionMatrix; // cached value

		// TO-DO: Refactor to a Transform class.
		glm::vec3 m_Location;
		glm::quat m_Rotation;
	};

}

