#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, uint32 numVerts)
{
	this->numVerts = numVerts;

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	GLCall(glGenBuffers(1, &bufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));

	// Position
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position)));
	// Norm
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal)));
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
	GLCall(glBindVertexArray(vao));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindVertexArray(0));
}