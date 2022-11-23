//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "perspectiveCamera.h"

/////////////
// CLASSES //
/////////////

PerspectiveCamera::PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float far, float near, float fov) :
	Camera(CameraType::ORTHOGRAPHIC, name, glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f), near, far) {};

void PerspectiveCamera::render() {
}