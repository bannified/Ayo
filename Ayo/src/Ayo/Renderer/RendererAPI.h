#pragma once

#include "glm/glm.hpp"
#include "Ayo/Renderer/VertexArray.h"

namespace Ayo {

	class AYO_API RendererAPI
	{
	public:

		enum class API
		{
			NONE = 0, // headless, server. no rendering required.
			OpenGL = 1,
		};

		inline static API GetCurrentAPI() { return s_CurrentAPI; }

	public:
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	private:
		static API s_CurrentAPI;
	};

}

