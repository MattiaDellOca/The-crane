#pragma once

#include "lib.h"
#include "object.h"

#include <iostream>

// GLM
#include <glm/glm.hpp>

class LIB_API Material : public Object {
private:
	glm::vec4 m_ambient = glm::vec4{ 0.2f, 0.2f, 0.2f, 1.0f };
	glm::vec4 m_diffuse = glm::vec4{ 0.8f, 0.8f, 0.8f, 1.0f };
	glm::vec4 m_specular = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
	glm::vec4 m_emission = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
	float m_shininess = 0.0f;
public:
	Material(std::string name);
	void apply();

	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setShininess(float);
	void setEmission(glm::vec4);

	glm::vec4 getAmbient() const;
	glm::vec4 getDiffuse() const;
	glm::vec4 getSpecular() const;
	glm::vec4 getEmission() const;
	float getShininess() const;
};