#pragma once

#include "positionalLight.h"

class LIB_API SpotLight : public PositionalLight {

private:
	float m_cutoff; //any angle between 0° and 90°
	glm::vec3 m_direction;

public:
	SpotLight(std::string, glm::mat4, glm::vec4, glm::vec4, glm::vec4, float, glm::vec3, float constantAttenuation = 1.f, float linearAttenuation = 0.f, float quadraticAttenuation = 0.f);

	virtual void render(glm::mat4);
};