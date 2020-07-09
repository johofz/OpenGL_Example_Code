#pragma once
#include "defines.h"
#include "vector"

struct BufferElement
{
	uint32 type;
	uint32 count;
	uint8 normalized;

	static uint32 GetSize(uint32 type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(0);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() 
		: stride(0) {};

	template<typename T>
	void Insert(uint32 count)
	{
		static_assert(false);
	}

	template<>
	void Insert<GLfloat>(uint32 count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * BufferElement::GetSize(GL_FLOAT);
	}

	template<>
	void Insert<GLuint>(uint32 count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * BufferElement::GetSize(GL_UNSIGNED_INT);
	}

	template<>
	void Insert<GLbyte>(uint32 count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		stride += count * BufferElement::GetSize(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<BufferElement> GetElements() const { return elements; }
	inline uint32 GetStride() const { return stride; }

private:
	std::vector<BufferElement> elements;
	uint32 stride;

};

