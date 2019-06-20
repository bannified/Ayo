#pragma once
#include "ayopch.h"
#include "Ayo/Renderer/Buffer.h"

namespace Ayo {
	
	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_Buffer;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline uint32_t GetCount() const override { return m_Count; }

		inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		const BufferLayout& GetLayout() const override { return m_Layout; };

	private:
		uint32_t m_Buffer;
		uint32_t m_Count;
		BufferLayout m_Layout;
	};


}

