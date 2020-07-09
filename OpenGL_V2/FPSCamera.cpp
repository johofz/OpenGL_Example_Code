#include "FPSCamera.h"

FPSCamera::FPSCamera(float32 fov, float32 width, float32 height) : Camera(fov, width, height)
{
	xRotation = -90.0f;
	yRotation = 0.0f;

	GetLineOfSight(0.0f, 0.0f);
	Update();
}

void FPSCamera::GetLineOfSight(float32 xRelative, float32 yRelative)
{
	xRotation += xRelative * sensitivity;
	yRotation -= yRelative * sensitivity;

	if (yRotation > 89.9f)
		yRotation = 89.9f;
	if (yRotation < -89.9f)
		yRotation = -89.9f;

	lineOfSight.x = cos(glm::radians(xRotation)) * cos(glm::radians(yRotation));
	lineOfSight.y = sin(glm::radians(yRotation));
	lineOfSight.z = sin(glm::radians(xRotation)) * cos(glm::radians(yRotation));

	lineOfSight = glm::normalize(lineOfSight);

	Update();
}

void FPSCamera::Update()
{
	view = glm::lookAt(position, position + lineOfSight, upwards);
	viewProjection = projection * view;
}

void FPSCamera::MoveFront(float32 increment)
{
	glm::vec3 direction = glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lineOfSight);
	Translate(direction * increment * cameraSpeed);
}

void FPSCamera::MoveSideways(float32 increment)
{
	glm::vec3 direction = glm::cross(lineOfSight, upwards);
	Translate(direction * increment * cameraSpeed);
}

void FPSCamera::MoveUp(float32 increment)
{
	Translate(upwards * increment * cameraSpeed);
}
