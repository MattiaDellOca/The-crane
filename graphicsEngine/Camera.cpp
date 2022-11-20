//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "Camera.h"


/////////////
// CLASSES //
/////////////

Camera::Camera(std::string name, glm::mat4 matrix, glm::mat4 projection, float near, float far)
	: Node(name, matrix), m_projection{ projection }, m_near{ near }, m_far{ far } {}

const glm::mat4& Camera::getProjection() {
	return m_projection;
}

const glm::mat4& Camera::getInverse() {
	return glm::inverse(m_projection);
}

float Camera::getNear() {
	return m_near;
}

float Camera::getFar() {
	return m_far;
}

void Camera::setProjection(glm::mat4 projection) {
	m_projection = projection;
}

void Camera::setNear(float near) {
	m_near = near;
}

void Camera::setFar(float far) {
	m_far = far;
}