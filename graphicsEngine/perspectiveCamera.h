#pragma once
//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "camera.h"

	// C/C++
#include <string>

	// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/////////////
// CLASSES //
/////////////

class LIB_API PerspectiveCamera : public Camera {
private:
	float m_fov;
public:
	PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float near, float far, float fov = 45.0f);
	void updateMatrix(unsigned int width, unsigned int height);
	virtual void render(glm::mat4);
	virtual void updateWindowSize(unsigned int width, unsigned int height);
};
