#include "Camera.h"

Camera::Camera(float32 fov, float32 width, float32 height)
{
	m_position = glm::vec3(0.0f);
	m_projection = glm::perspective(glm::radians(fov / 2.0f), width / height, 0.1f, 1500.0f);
	m_view = glm::mat4(1.0f);

}

void Camera::Translate(glm::vec3 translation)
{
	m_position += translation;
	m_view = glm::translate(m_view, translation * -1.0f);
}
