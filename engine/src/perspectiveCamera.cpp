//////////////
// #INCLUDE //
//////////////

#include "engine.h"
#include "shaderManager.h"

	// Library main include
#include "perspectiveCamera.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>


/////////////
// CLASSES //
/////////////

LIB_API PerspectiveCamera::PerspectiveCamera(const std::string& name, glm::mat4 matrix, unsigned int width, unsigned int height, float nearPlane, float farPlane, float fov) :
	Camera(CameraType::PERSPECTIVE, name, matrix, nearPlane, farPlane, width, height), m_fov{ fov } {
	m_properties = glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);
};

void LIB_API PerspectiveCamera::render(glm::mat4 matrix) {
	ShaderManager::GetShader("programShader")->setMatrix(ShaderManager::GetShader("programShader")->getParamLocation("projection"), matrix);
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
	*/
}

void LIB_API PerspectiveCamera::updateWindowSize(unsigned int width, unsigned int height) {
	// Update width + matrix fields
	m_width = width;
	m_height = height;

	// Recalculate perspective matrix
	m_properties = glm::perspective(glm::radians(m_fov), (float)width / (float)height, m_near, m_far);
}
