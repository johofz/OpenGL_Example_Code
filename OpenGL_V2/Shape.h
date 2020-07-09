#pragma once
#include "defines.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Shape
{
public:

	virtual ~Shape();
	
	void CreateVertexBuffer(void* data, uint32 numVerts);
	void CreateIndexBuffer(void* data, uint32 numIndices, uint8 size);

	void Bind();
	void Unbind();

	virtual void Move(glm::vec3 translation);
	virtual void Draw();

	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	glm::vec3 GetPosition();
	glm::vec3 GetInitialPosition();

	void UpdateVertexBuffer(void* data);
	void SetMaterial(Material material);
	void SetShaderSettings();

protected:
	glm::vec3 position;
	glm::vec3 initialPosition;

	Material material = {};

	Shader* shader;
	int diffusionLoc;
	int specularLoc;
	int emissiveLoc;
	int shineLoc;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
};

