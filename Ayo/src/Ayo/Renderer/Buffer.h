#pragma once

namespace Ayo {

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		AYO_CORE_ASSERT(false, "Invalid or unknown ShaderDataType.");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement()
			: Name(""), Type(ShaderDataType::None), Size(0), Offset(0), Normalized(false) { }

		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) { }

		inline uint32_t GetComponentCount() const
		{
			switch (Type) {
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Bool:		return 1;
			}

			AYO_CORE_ASSERT(false, "Invalid or unknown ShaderDataType.");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout()
			: m_Elements({}) {};

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements) 
		{
			CalculateOffsetsAndStride();
		};

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.cend(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		void CalculateOffsetsAndStride()
		{
			int offset = 0;
			m_Stride = 0;
			for (auto& e : m_Elements) {
				m_Stride += e.Size;
				e.Offset = offset;
				offset += e.Size;
			}
		}
	};

	class VertexBuffer
	{
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static std::shared_ptr<VertexBuffer> Create(const void* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;		

		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}

