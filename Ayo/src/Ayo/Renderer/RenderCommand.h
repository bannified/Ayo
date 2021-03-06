#pragma once

#include "glm/glm.hpp"

#include "Ayo/Renderer/VertexArray.h"
#include "Ayo/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ayo {

	class AYO_API RenderCommand
	{
	public:

		static void SetClearColor(const glm::vec4 color);
		static void Clear();
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

        static void SetWireframeMode(bool isWireframeMode);

        static void BeginScene();
        static void EndScene();
	
	private:
		static RendererAPI* s_RendererAPI;
	};

}

