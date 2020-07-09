#include "Cube.h"

Cube::Cube(glm::vec3 center, float32 width, Shader* shader)
{
	position = center;
	initialPosition = center;

	this->width = width;
	this->height = width;
	this->depth = width;

	this->shader = shader;

	SetShaderSettings();

	UpdateVerts();
	CreateVertexBuffer(verts, numVerts);

	uint32 indices[] = {
			0, 1, 2,	2, 3, 0,	// Front
			5, 4, 7,	7, 6, 5,	// Back 
			8, 9, 10,	10, 11, 8,	// Right
			13, 12, 15, 15, 14, 13,	// Left
			16, 17, 18, 18, 19, 16, // Top
			21, 20, 23, 23, 22, 21	// Bottom
	};

	CreateIndexBuffer(indices, numIndices, sizeof(indices[0]));
}

void Cube::UpdateVerts()
{
	// Front
	verts[0] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[1] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[2] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[3] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};

	// Back
	verts[4] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[5] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[6] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};
	verts[7] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.0f, 0.5f)
	};

	// Right
	verts[8] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	verts[9] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	verts[10] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	verts[11] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};

	// Left
	verts[12] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.5f, 0.0f, 0.0f)
	};
	verts[13] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.5f, 0.0f, 0.0f)
	};
	verts[14] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.5f, 0.0f, 0.0f)
	};
	verts[15] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.5f, 0.0f, 0.0f)
	};

	// Top
	verts[16] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	verts[17] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	verts[18] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	verts[19] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y + height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	// Bottom
	verts[20] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};
	verts[21] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z - depth / 2.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};
	verts[22] = Vertex{
		glm::vec3(position.x + width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};
	verts[23] = Vertex{
		glm::vec3(position.x - width / 2.0f, position.y - height / 2.0f, position.z + depth / 2.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};
}

void Cube::Move(glm::vec3 translation)
{
	position += translation;
	UpdateVerts();
	vertexBuffer->Update(verts);
}

void Cube::Draw()

{
	GLCall(glUniform3fv(diffusionLoc, 1, &material.diffuse.x));
	GLCall(glUniform3fv(specularLoc, 1, &material.specular.x));
	GLCall(glUniform3fv(emissiveLoc, 1, &material.emissive.x));
	GLCall(glUniform1f(shineLoc, material.shine));

	Bind();
	GLCall(glDrawElements(GL_TRIANGLES, GetIndexBuffer()->GetNumIndices(), GL_UNSIGNED_INT, nullptr));
	Unbind();
}
