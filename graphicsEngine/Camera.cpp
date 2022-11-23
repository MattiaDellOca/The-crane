//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "camera.h"


/////////////
// CLASSES //
/////////////

Camera::Camera(CameraType type, std::string name, glm::mat4 matrix, float near, float far) :
	Node(name, matrix), m_near{ near }, m_far{ far }, m_type{ type } {};

float Camera::getNear() {
	return m_near;
}

float Camera::getFar() {
	return m_far;
}

void Camera::setNear(float near) {
	m_near = near;
}

void Camera::setFar(float far) {
	m_far = far;
}

void Camera::render() {
	//TODO
}
