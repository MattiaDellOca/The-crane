
#include "material.h"


   //GLM:
#include <glm/gtc/type_ptr.hpp>

   //FreeGLUT:
#include <GL/freeglut.h>

LIB_API Material::Material(std::string name) : Object{ name } {};

void LIB_API Material::apply() {
	std::cout << "APPLING MATERIAL: name: " << m_name << "id: " << m_id << std::endl;
	// Set material properties:
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
}

// GETTER + SETTERS

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

void LIB_API Material::setEmission(glm::vec4 emission) {
	m_emission = emission;
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

glm::vec4 LIB_API Material::getEmission() const {
	return m_emission;
}


void LIB_API Material::render(glm::mat4 matrix) {
	std::cout << "MATERIAL: name: " << m_name << "id: " << m_id << std::endl;
}