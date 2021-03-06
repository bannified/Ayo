#pragma once
#include "Ayo/Renderer/Buffer.h"

namespace Ayo {
	
	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(const void* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout;	};
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };

	private:
		uint32_t m_Buffer;
		BufferLayout m_Layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline uint32_t GetCount() const override { return m_Count; }

		

	private:
		uint32_t m_Buffer;
		uint32_t m_Count;
	};


}

