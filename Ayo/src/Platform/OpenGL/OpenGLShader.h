#pragma once

#include "Ayo/Renderer/Shader.h"

#include "glm/glm.hpp"

namespace Ayo
{
    class Texture;

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string vertexSource, const std::string fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

        static std::shared_ptr<OpenGLShader> CreateFromPath(const std::string& vertexPath, const std::string& fragmentPath);


        virtual void UpdateIntConstant(const std::string& constantName, int value) override;

        virtual void UpdateFloatConstant(const std::string& constantName, float value) override;
        virtual void UpdateFloat2Constant(const std::string& constantName, const glm::vec2& value) override;
        virtual void UpdateFloat3Constant(const std::string& constantName, const glm::vec3& value) override;
        virtual void UpdateFloat4Constant(const std::string& constantName, const glm::vec4& value) override;

        virtual void UpdateMat3Constant(const std::string& constantName, const glm::mat3& value) override;
        virtual void UpdateMat4Constant(const std::string& constantName, const glm::mat4& value) override;

        virtual void AddTexture(const std::string& constantName, const std::shared_ptr<Texture>& texture) override;

    private:
        void UpdateIntUniform(const std::string& uniformName, int value);

        void UpdateFloatUniform(const std::string& uniformName, float value);
        void UpdateFloat2Uniform(const std::string& uniformName, const glm::vec2& value);
        void UpdateFloat3Uniform(const std::string& uniformName, const glm::vec3& value);
        void UpdateFloat4Uniform(const std::string& uniformName, const glm::vec4& value);

        void UpdateMat3Uniform(const std::string& uniformName, const glm::mat3& value);
        void UpdateMat4Uniform(const std::string& uniformName, const glm::mat4& value);

		uint32_t m_RendererId;

        mutable int m_NextTextureIndex;

	};
}

