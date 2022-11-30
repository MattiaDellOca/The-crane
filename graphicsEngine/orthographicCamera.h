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
	OrthographicCamera(std::string name, unsigned int width, unsigned int height);
	void render();
};
