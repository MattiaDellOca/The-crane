#pragma once

#include "light.h"

class LIB_API PositionalLight : public Light {

protected: 
	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;
	PositionalLight(std::string, glm::mat4, LightType, glm::vec4, glm::vec4, glm::vec4, float constantAttenuation = 1.f, float linearAttenuation = 0.f,float quadraticAttenuation = 0.f);

public: 
	virtual void render(glm::mat4) = 0;
};