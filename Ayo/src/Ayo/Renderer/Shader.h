#pragma once

namespace Ayo {

    class Texture;

	class Shader
	{
	public:
		Shader();

		~Shader();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

        virtual void UpdateIntConstant(const std::string& constantName, int value) = 0;

        virtual void UpdateFloatConstant(const std::string& constantName, float value) = 0;
        virtual void UpdateFloat2Constant(const std::string& constantName, const glm::vec2& value) = 0;
        virtual void UpdateFloat3Constant(const std::string& constantName, const glm::vec3& value) = 0;
        virtual void UpdateFloat4Constant(const std::string& constantName, const glm::vec4& value) = 0;

        virtual void UpdateMat3Constant(const std::string& constantName, const glm::mat3& value) = 0;
        virtual void UpdateMat4Constant(const std::string& constantName, const glm::mat4& value) = 0;

        virtual void AddTexture(const std::string& constantName, const std::shared_ptr<Texture>& texture) = 0;

        static std::shared_ptr<Shader> Create(const std::string vertexSource, const std::string fragmentSource);
        static std::shared_ptr<Shader> CreateFromPath(const std::string vertexSource, const std::string fragmentSource);
	};

}