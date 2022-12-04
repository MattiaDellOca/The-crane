#include "light.h"

glm::vec4 LIB_API Light::getAmbient() {
	return m_ambient;
}

glm::vec4 LIB_API Light::getDiffuse() {
	return m_diffuse;
}

glm::vec4 LIB_API Light::getSpecular() {
	return m_specular;
}

void LIB_API Light::setAmbient(glm::vec4 ambient) {
	m_ambient = ambient;
}

void LIB_API Light::setDiffuse(glm::vec4 diffuse) {
	m_diffuse = diffuse;
}

void LIB_API Light::setSpecular(glm::vec4 specular) {
	m_specular = specular;
}