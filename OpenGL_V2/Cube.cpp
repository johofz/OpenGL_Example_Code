#include "Cube.h"

Cube::Cube(const glm::vec3& center, float32 width, const glm::vec3& color, Shader* shader)
{
	m_width = width;
	m_position = center;
	m_initialPosition = m_position;

	m_shader = shader;
	ShaderSetColor(color);

	UpdateVerts();
	CreateVertexArray(m_verts, m_numVerts);

	uint32 indices[] = {
			0, 1, 2,	2, 3, 0,	// Front
			5, 4, 7,	7, 6, 5,	// Back 
			8, 9, 10,	10, 11, 8,	// Right
			13, 12, 15, 15, 14, 13,	// Left
			16, 17, 18, 18, 19, 16, // Top
			21, 20, 23, 23, 22, 21	// Bottom
	};

	CreateIndexBuffer(indices, m_numIndices, sizeof(indices[0]));
}

void Cube::UpdateVerts()
{
	// Front
	m_verts[0] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
	m_verts[1] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
	m_verts[2] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
	m_verts[3] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	// Back
	m_verts[4] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f)
	};
	m_verts[5] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f)
	};
	m_verts[6] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f)
	};
	m_verts[7] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f)
	};

	// Right
	m_verts[8] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	m_verts[9] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	m_verts[10] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};
	m_verts[11] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	};

	// Left
	m_verts[12] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	};
	m_verts[13] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	};
	m_verts[14] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	};
	m_verts[15] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	};

	// Top
	m_verts[16] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	m_verts[17] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	m_verts[18] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	m_verts[19] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y + m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	// Bottom
	m_verts[20] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
	};
	m_verts[21] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z + m_width / 2.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
	};
	m_verts[22] = Vertex{
		glm::vec3(m_position.x + m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
	};
	m_verts[23] = Vertex{
		glm::vec3(m_position.x - m_width / 2.0f, m_position.y - m_width / 2.0f, m_position.z - m_width / 2.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
	};
}

void Cube::Move(glm::vec3 translation)
{
	m_position += translation;
	UpdateVerts();
	m_vertexBuffer->Update(m_verts);
}

void Cube::Draw()
{
	Bind();
	GLCall(glDrawElements(GL_TRIANGLES, GetIndexBuffer()->GetNumIndices(), GL_UNSIGNED_INT, 0));
}
