#include "ayopch.h"

#include "Shader.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ayo {

	Shader::Shader()
	{
		
	}

	Shader::~Shader()
	{

	}

     std::shared_ptr<Shader> Shader::Create(const std::string vertexSource, const std::string fragmentSource)
	{
		switch (RendererAPI::GetCurrentAPI()) 
		{
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
			case RendererAPI::API::NONE:
				AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
				return nullptr;
		}

		AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
		return nullptr;
	}

    std::shared_ptr<Shader> Shader::CreateFromPath(const std::string vertexPath, const std::string fragmentPath)
    {
        switch (RendererAPI::GetCurrentAPI()) {
            case RendererAPI::API::OpenGL:
                return OpenGLShader::CreateFromPath(vertexPath, fragmentPath);
            case RendererAPI::API::NONE:
                AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
                return nullptr;
        }

        AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
        return nullptr;
    }

}

