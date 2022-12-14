#pragma once

#include "node.h"
#include "lightType.h"

class LIB_API Light : public Node {
protected:
	static unsigned int m_baseValueLights;
	static unsigned int m_incrementalLightId;
	static int m_maxLights; //max lights that opengl can manage 
	LightType m_type;
	unsigned int m_lightId;
	glm::vec4 m_lightAmbient;
	glm::vec4 m_lightDiffuse;
	glm::vec4 m_lightSpecular;
	Light(std::string, glm::mat4, LightType, glm::vec4, glm::vec4, glm::vec4);

public:
	void virtual render(glm::mat4) = 0;
};