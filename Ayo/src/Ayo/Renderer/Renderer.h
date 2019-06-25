#pragma once

#include "Ayo/Renderer/RenderCommand.h"
#include "Ayo/Renderer/RendererAPI.h"
#include "Ayo/Renderer/VertexArray.h"

namespace Ayo {

	class Renderer
	{
	public:
		static void BeginScene();
		static void Submit(const std::shared_ptr<VertexArray> vertexArray);
		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetCurrentAPI(); }
	};

}

