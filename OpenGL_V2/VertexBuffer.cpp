#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, uint32 numVerts)
{
	GLCall(glGenBuffers(1, &bufferID));
	this->numVerts = numVerts;
	Update(data);
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &bufferID));
}

void VertexBuffer::Update(void* data)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex), data, GL_DYNAMIC_DRAW));
	Unbind();
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}