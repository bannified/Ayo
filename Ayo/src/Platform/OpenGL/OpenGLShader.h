#pragma once

#include "Ayo/Renderer/Shader.h"

#include "glm/glm.hpp"

namespace Ayo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string vertexSource, const std::string fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UpdateFloatInt(const std::string& uniformName, int value);

		void UpdateFloatUniform(const std::string& uniformName, float value);
		void UpdateFloat2Uniform(const std::string& uniformName, const glm::vec2& value);
		void UpdateFloat3Uniform(const std::string& uniformName, const glm::vec3& value);
		void UpdateFloat4Uniform(const std::string& uniformName, const glm::vec4& value);

		void UpdateMat3Uniform(const std::string& uniformName, const glm::mat3& value);
		void UpdateMat4Uniform(const std::string& uniformName, const glm::mat4& value);

	private:
		uint32_t m_RendererId;

	};
}

