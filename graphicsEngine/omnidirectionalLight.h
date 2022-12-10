#pragma once

#include "lib.h"
#include "light.h"
#include "lightType.h"

class LIB_API OmnidirectionalLight : public Light {

public:
	OmnidirectionalLight(std::string, glm::mat4, unsigned int, glm::vec4, glm::vec4, glm::vec4);

	virtual void render(glm::mat4);
};