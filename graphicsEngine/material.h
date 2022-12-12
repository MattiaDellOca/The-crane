#pragma once

#include "lib.h"
#include "object.h"

#include <iostream>

// GLM
#include <glm/glm.hpp>

class LIB_API Material : public Object {
private:
	glm::vec3 m_materialColor;
	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
	glm::vec4 m_emission;
	float m_shininess;
public:
	Material(std::string name);
	void apply();
	void render(glm::mat4);

	void setMaterialColor(glm::vec3);
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setShininess(float);
	void setEmission(glm::vec4);

	glm::vec3 getMaterialColor() const;
	glm::vec4 getAmbient() const;
	glm::vec4 getDiffuse() const;
	glm::vec4 getSpecular() const;
	glm::vec4 getEmission() const;
	float getShininess() const;
};