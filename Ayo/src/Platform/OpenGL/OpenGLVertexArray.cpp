#include "ayopch.h"

#include "OpenGLVertexArray.h"

#include "Ayo/Core.h"
#include "Ayo/Renderer/Buffer.h"

#include "glad/glad.h"

namespace Ayo {

	static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		AYO_CORE_ASSERT(false, "Invalid or unknown ShaderDataType.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArray);
		
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteBuffers(1, &m_VertexArray);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_VertexArray);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		AYO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout.");

		glBindVertexArray(m_VertexArray);
		vertexBuffer->Bind();

		int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
								  e.GetComponentCount(),
								  ShaderDataTypeToGLenum(e.Type),
								  e.Normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (const void*)e.Offset);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VertexArray);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}