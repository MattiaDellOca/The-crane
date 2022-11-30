#pragma once
//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "node.h"
#include "cameraType.h"

	// C/C++
#include <string>

	// GLM:
#include <glm/glm.hpp>


/////////////
// CLASSES //
/////////////

class LIB_API Camera : public Node {
protected:
	unsigned int m_width;
	unsigned int m_height;
	float m_near;
	float m_far;
	CameraType m_type;
public:
	Camera(CameraType type, std::string name, glm::mat4 matrix, float near, float far, float width, float height);

	float getNear();
	float getFar();
	void setNear(float);
	void setFar(float);
	void virtual render() = 0;
};
