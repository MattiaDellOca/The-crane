
//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "orthographicCamera.h"

/////////////
// CLASSES //
/////////////

OrthographicCamera::OrthographicCamera(std::string name, unsigned int width, unsigned int height) :
	Camera(CameraType::ORTHOGRAPHIC, name, glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f), -1.0, 1.0f) {};

void OrthographicCamera::render() {
}