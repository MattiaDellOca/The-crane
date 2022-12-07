
#include "material.h"

LIB_API Material::Material(std::string name) : Object{ name } {};

void LIB_API Material::apply() {
	/*
		// Set material properties:
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, powf(2.0f, 5));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	*/
}

// GETTER + SETTERS

void LIB_API Material::setMaterialColor(glm::vec3 color) {
	m_materialColor = color;
}

void LIB_API Material::setAmbient(glm::vec4 ambient) {
	m_ambient = ambient;
}

void LIB_API Material::setDiffuse(glm::vec4 diffuse) {
	m_diffuse = diffuse;
}

void LIB_API Material::setSpecular(glm::vec4 specular) {
	m_specular = specular;
}

void LIB_API Material::setShininess(float shininess) {
	m_shininess = shininess;
}

glm::vec3 LIB_API Material::getMaterialColor() const {
	return m_materialColor;
}

glm::vec4 LIB_API Material::getAmbient() const {
	return m_ambient;
}

glm::vec4 LIB_API Material::getDiffuse() const {
	return m_diffuse;
}

glm::vec4 LIB_API Material::getSpecular() const {
	return m_specular;
}

float LIB_API Material::getShininess() const {
	return m_shininess;
}

void LIB_API Material::render(glm::mat4 matrix) {
	std::cout << "MATERIAL: name: " << m_name << "id: " << m_id << std::endl;
}