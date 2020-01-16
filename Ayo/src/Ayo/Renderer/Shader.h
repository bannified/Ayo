#pragma once

namespace Ayo {

	class Shader
	{
	public:
		Shader();

		~Shader();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

        static std::shared_ptr<Shader> Create(const std::string vertexSource, const std::string fragmentSource);
        static std::shared_ptr<Shader> CreateFromPath(const std::string vertexSource, const std::string fragmentSource);
	};

}