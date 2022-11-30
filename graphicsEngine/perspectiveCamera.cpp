//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "perspectiveCamera.h"

/////////////
// CLASSES //
/////////////

LIB_API PerspectiveCamera::PerspectiveCamera(std::string name, unsigned int width, unsigned int height, float near, float far, float fov) :
	Camera(CameraType::ORTHOGRAPHIC, name, glm::perspective(glm::radians(45.0f), (float)width / (float)height, near, far), near, far) {};

void LIB_API PerspectiveCamera::render() {
}

void LIB_API updateMatrix(unsigned int width, unsigned int height) {

}
