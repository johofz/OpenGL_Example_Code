#include "Shape.h"


Shape::~Shape()
{
}

void Shape::CreateVertexBuffer(void* data, uint32 numVerts)
{
	vertexBuffer = new VertexBuffer(data, numVerts);
}

void Shape::CreateIndexBuffer(void* data, uint32 numIndices, uint8 size)
{
	indexBuffer = new IndexBuffer(data, numIndices, size);
}

void Shape::Bind()
{
	vertexBuffer->Bind();
	indexBuffer->Bind();
}

void Shape::Unbind()
{
	indexBuffer->Unbind();
	vertexBuffer->Unbind();
}

void Shape::Move(glm::vec3 translation)
{
}

void Shape::Draw()
{
}

VertexBuffer* Shape::GetVertexBuffer()
{
	return vertexBuffer;
}

IndexBuffer* Shape::GetIndexBuffer()
{
	return indexBuffer;
}

glm::vec3 Shape::GetPosition()
{
	return position;
}

glm::vec3 Shape::GetInitialPosition()
{
	return initialPosition;
}

void Shape::UpdateVertexBuffer(void* data)
{
	vertexBuffer->Update(data);
}

void Shape::SetMaterial(Material material)
{
	this->material = material;
}

void Shape::SetShaderSettings()
{
	GLCall(diffusionLoc = glGetUniformLocation(shader->GetShaderID(), "u_material.diffuse"));
	ASSERT(diffusionLoc != -1);

	GLCall(specularLoc = glGetUniformLocation(shader->GetShaderID(), "u_material.specular"));
	ASSERT(specularLoc != -1);

	GLCall(emissiveLoc = glGetUniformLocation(shader->GetShaderID(), "u_material.emissive"));
	ASSERT(emissiveLoc != -1);

	GLCall(shineLoc = glGetUniformLocation(shader->GetShaderID(), "u_material.shine"));
	ASSERT(shineLoc != -1);

}

