#pragma once

#include "lib.h"
#include "node.h"
#include "lightType.h"

#include <glm/glm.hpp>

class LIB_API Light : public Node {
protected:
	LightType m_type;
	unsigned int m_lightId;
	glm::vec3 m_lightPosition; //maybe this will be delete because is ever 0,0,0
	glm::vec4 m_lightAmbient;
	glm::vec4 m_lightDiffuse;
	glm::vec4 m_lightSpecular;
public:
	Light(std::string, glm::mat4, LightType, unsigned int, glm::vec4, glm::vec4, glm::vec4);

	//Factory method
	//Light create(std::string, glm::mat4 ,LightType, unsigned int, glm::vec4, glm::vec4, glm::vec4);

	void virtual render(glm::mat4) = 0;
};