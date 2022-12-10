#pragma once

#include "lib.h"
#include "light.h"
#include "lightType.h"

class LIB_API SpotLight : public Light {

private:
	float m_cutoff; //any angle between 0° and 90°

public:
	SpotLight(std::string, glm::mat4, unsigned int, glm::vec4, glm::vec4, glm::vec4, float);

	virtual void render(glm::mat4);
};