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
	glm::mat4 m_properties;
	unsigned int m_width;
	unsigned int m_height;
	float m_near;
	float m_far;
	CameraType m_type;
public:
	Camera(CameraType type, std::string name, glm::mat4 matrix, float near, float far, unsigned int width, unsigned int height);

	float getNear() const;
	float getFar() const;
	void setNear(float);
	void setFar(float);

	void setWidth(unsigned int);
	void setHeight(unsigned int);
	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void virtual render(glm::mat4) = 0;
	void virtual updateWindowSize(unsigned int, unsigned int) = 0;
};
