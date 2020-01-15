#pragma once

#include "Ayo/Renderer/RendererAPI.h"

namespace Ayo {

	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();

		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

        virtual void SetWireframeMode(bool isWireframe) override;

    };

}

