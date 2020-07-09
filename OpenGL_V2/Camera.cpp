#include "Camera.h"

Camera::Camera(float32 fov, float32 width, float32 height)
{
	position = glm::vec3(0.0f);
	projection = glm::perspective(glm::radians(fov / 2.0f), width / height, 0.1f, 1500.0f);
	view = glm::mat4(1.0f);
	Update();
}

void Camera::Update()
{
	viewProjection = projection * view;
}

void Camera::Translate(glm::vec3 translation)
{
	position += translation;
	view = glm::translate(view, translation * -1.0f);
}

glm::mat4 Camera::GetViewProjection()
{	
	return viewProjection;;
}

glm::mat4 Camera::GetView()
{
	return view;
}

glm::vec3 Camera::GetPosition()
{
	return position;
}
