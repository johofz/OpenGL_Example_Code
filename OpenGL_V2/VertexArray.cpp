#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &vao));
}

void VertexArray::InsertBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
	Bind();
	buffer.Bind();
	const std::vector<BufferElement> elements = layout.GetElements();
	uint32 offset = 0;
	for (uint32 i = 0; i < elements.size(); i++)
	{
		const BufferElement element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * BufferElement::GetSize(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(vao));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
