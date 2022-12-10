#pragma once

#include "light.h"

class LIB_API SpotLight : public Light {

private:
	float m_cutoff; //any angle between 0° and 90°
	glm::vec3 m_direction;

public:
	SpotLight(std::string, glm::mat4, unsigned int, glm::vec4, glm::vec4, glm::vec4, float, glm::vec3);

	virtual void render(glm::mat4);
};