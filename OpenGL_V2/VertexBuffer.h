#pragma once
#include "defines.h"
#include <GL/glew.h>

class VertexBuffer
{
public: 
	VertexBuffer(void* data, uint32 numVerts);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void Update(void* data);

private:
	GLuint bufferID;
	uint32 numVerts;
};

