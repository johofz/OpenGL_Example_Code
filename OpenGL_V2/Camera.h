#pragma once
#include "defines.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera
{
public:
	Camera(float32 fov, float32 width, float32 heigth);

	virtual void Update();
	void Translate(glm::vec3 translation);

	glm::mat4 GetViewProjection();
	glm::mat4 GetView();
	glm::vec3 GetPosition();

protected:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProjection;
};

