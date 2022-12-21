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

class LIB_API OrthographicCamera : public Camera {
public:
	OrthographicCamera(std::string name, glm::mat4 matrix, unsigned int width, unsigned int height);
	virtual void render(glm::mat4);
	virtual void updateWindowSize(unsigned int width, unsigned int height);
};
