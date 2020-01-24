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

		void RecalculateViewProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;

		glm::mat4 m_ViewProjectionMatrix; // cached value
	};

}

