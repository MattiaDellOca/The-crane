//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "perspectiveCamera.h"

/////////////
// CLASSES //
/////////////

LIB_API PerspectiveCamera::PerspectiveCamera(std::string name, glm::mat4 matrix, unsigned int width, unsigned int height, float near, float far, float fov) :
	Camera(CameraType::PERSPECTIVE, name, matrix, near, far, width, height), m_fov{ fov } {
	m_properties = glm::perspective(glm::radians(fov), (float)width / (float)height, near, far);
};

void LIB_API PerspectiveCamera::render(glm::mat4 matrix) {
	std::cout << "Rendering perspective camera" << std::endl;
}

void LIB_API PerspectiveCamera::updateWindowSize(unsigned int width, unsigned int height) {
	// Update width + matrix fields
	m_width = width;
	m_height = height;

	// Recalculate perspective matrix
	m_properties = glm::perspective(glm::radians(m_fov), (float)width / (float)height, m_near, m_far);
}
