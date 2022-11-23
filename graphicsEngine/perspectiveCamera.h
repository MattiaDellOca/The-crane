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

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float far, float near, float fov = 45.0f);
	void render();
};
