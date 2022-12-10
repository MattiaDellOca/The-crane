#pragma once

#include "light.h"

class LIB_API OmnidirectionalLight : public Light {

public:
	OmnidirectionalLight(std::string, glm::mat4, unsigned int, glm::vec4, glm::vec4, glm::vec4);

	virtual void render(glm::mat4);
};