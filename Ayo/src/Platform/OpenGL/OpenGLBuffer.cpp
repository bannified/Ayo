#include "ayopch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Ayo {

	/*
		Vertex Buffer Definitions
	*/
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_Buffer);
		glNamedBufferStorage(m_Buffer, size, vertices, 0);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Buffer);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*
		Index Buffer Definitions
	*/

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_Buffer);
		glNamedBufferStorage(m_Buffer, count * sizeof(uint32_t), indices, 0);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Buffer);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}