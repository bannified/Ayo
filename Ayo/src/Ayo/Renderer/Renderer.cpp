#include "ayopch.h"
#include "Renderer.h"

namespace Ayo {

    std::shared_ptr<Ayo::Camera> Renderer::m_ViewCamera;

	void Renderer::BeginScene(const std::shared_ptr<Camera>& viewCamera)
	{
		// TODO
        m_ViewCamera = viewCamera;
        RenderCommand::BeginScene();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> vertexArray)
	{
        shader->Bind();

        shader->UpdateFloat3Constant("u_ViewPosition", m_ViewCamera->GetLocalLocation().Get());
        shader->UpdateMat4Constant("u_ViewProjectionMatrix", m_ViewCamera->GetViewProjectionMatrix());

		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		//TODO
        RenderCommand::EndScene();
	}

}
