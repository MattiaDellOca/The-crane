//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "perspectiveCamera.h"

/////////////
// CLASSES //
/////////////

PerspectiveCamera::PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float near, float far, float fov) :
	Camera(CameraType::ORTHOGRAPHIC, name, glm::perspective(glm::radians(45.0f), (float)width / (float)height, near, far), near, far) {};

void PerspectiveCamera::render() {
}
