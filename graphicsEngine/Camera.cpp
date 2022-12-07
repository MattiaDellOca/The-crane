//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "camera.h"


/////////////
// CLASSES //
/////////////

LIB_API Camera::Camera(CameraType type, std::string name, glm::mat4 matrix, float near, float far, unsigned int width, unsigned int height) :
	Node(name, matrix), m_near{ near }, m_far{ far }, m_type{ type }, m_width{ width }, m_height{ height } {};

float LIB_API Camera::getNear() const {
	return m_near;
}

float LIB_API Camera::getFar() const {
	return m_far;
}

unsigned int LIB_API Camera::getWidth() const {
	return m_width;
}

unsigned int LIB_API Camera::getHeight() const {
	return m_height;
}

void LIB_API Camera::setWidth(unsigned int width) {
	m_width = width;
}

void LIB_API Camera::setHeight(unsigned int height) {
	m_height = height;
}

void LIB_API Camera::setNear(float near) {
	m_near = near;
}

void LIB_API Camera::setFar(float far) {
	m_far = far;
}

void LIB_API Camera::render(glm::mat4) {
	//TODO
}
