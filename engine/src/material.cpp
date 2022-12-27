
#include "material.h"


   //GLM:
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>

   //FreeGLUT:
#include <GL/freeglut.h>

LIB_API Material::Material(std::string name) : Object{ name }, m_texture{nullptr} {};

void LIB_API Material::apply() {
	// Set material properties:
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));

	// Apply texture if present
	if (m_texture != nullptr) {
		m_texture->render(glm::mat4(1.0f));
	}
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

Texture LIB_API* Material::getTexture() const {
	return m_texture;
}

void LIB_API Material::setTexture(Texture* texture) {
	m_texture = texture;
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

void LIB_API Material::render(glm::mat4 coords)
{
}

glm::vec4 LIB_API Material::getEmission() const {
	return m_emission;
}