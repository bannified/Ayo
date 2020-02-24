#pragma once

#include "Ayo/Renderer/RenderCommand.h"
#include "Ayo/Renderer/RendererAPI.h"
#include "Ayo/Renderer/VertexArray.h"
#include "Ayo/Renderer/Camera.h"
#include "Ayo/Renderer/Shader.h"

namespace Ayo {

	class AYO_API Renderer
	{
	public:
		static void BeginScene(const std::shared_ptr<Camera>& viewCamera);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> vertexArray);
		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetCurrentAPI(); }

    private:

        static std::shared_ptr<Camera> m_ViewCamera;
	};

}

