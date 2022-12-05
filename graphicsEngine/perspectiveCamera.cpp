//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "perspectiveCamera.h"

/////////////
// CLASSES //
/////////////

LIB_API PerspectiveCamera::PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float near, float far, float fov) :
	Camera(CameraType::PERSPECTIVE, name, glm::perspective(glm::radians(fov), (float)width / (float)height, near, far), near, far, width, height) {};

void LIB_API PerspectiveCamera::render() {
	std::cout << "Rendering perspective camera" << std::endl;
}

void LIB_API PerspectiveCamera::updateWindowSize(unsigned int width, unsigned int height) {
	// Update width + matrix fields
	m_width = width;
	m_height = height;

	// Recalculate perspective matrix
	m_matrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, m_near, m_far);
}
