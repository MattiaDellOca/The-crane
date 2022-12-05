#pragma once

#include "lib.h"
#include "node.h"

#include <glm/glm.hpp>

class LIB_API Light : public Node {
protected:
	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
public:
	Light(std::string name, glm::mat4 matrix);
	glm::vec4 getAmbient();
	glm::vec4 getDiffuse();
	glm::vec4 getSpecular();
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	// Make this pure virtual
	void virtual render();
};