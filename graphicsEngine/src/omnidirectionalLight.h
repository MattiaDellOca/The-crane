#pragma once

#include "positionalLight.h"

class LIB_API OmnidirectionalLight : public PositionalLight {

public:
	OmnidirectionalLight(std::string, glm::mat4, glm::vec4, glm::vec4, glm::vec4, float constantAttenuation = 1.f, float linearAttenuation = 0.f, float quadraticAttenuation = 0.f);
	virtual void render(glm::mat4);
};