#pragma once
#include "defines.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"


class Camera
{
public:
	Camera(float32 fov, float32 width, float32 heigth);

	void Translate(glm::vec3 translation);

	const glm::mat4& GetView() const { return m_view; };
	const glm::mat4& GetProjection() const { return m_projection; };
	const glm::vec3& GetPosition() const { return m_position; };


protected:
	glm::vec3 m_position;
	glm::mat4 m_projection;
	glm::mat4 m_view;
};

