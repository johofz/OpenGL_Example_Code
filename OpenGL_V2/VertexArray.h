#pragma once
#include "defines.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void InsertBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
private:
	GLuint vao;
};

