
//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "orthographicCamera.h"

#include <glm/gtc/type_ptr.hpp>

/////////////
// CLASSES //
/////////////

LIB_API OrthographicCamera::OrthographicCamera(std::string name, glm::mat4 matrix, unsigned int width, unsigned int height) :
	Camera(CameraType::ORTHOGRAPHIC, name, matrix, -1.0, 1.0f, width, height) {
	m_properties = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}

void LIB_API OrthographicCamera::render(glm::mat4 matrix) {
	std::cout << "Rendering perspective camera" << std::endl;
}

void LIB_API OrthographicCamera::updateWindowSize(unsigned int width, unsigned int height) {
	// Update width + matrix fields
	m_width = width;
	m_height = height;

	// Recalculate orthographic matrix
	m_properties = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}