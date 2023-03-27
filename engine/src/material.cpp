
#include "material.h"
#include "shaderManager.h"


   //GLM:
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

   //FreeGLUT:
#include <GL/freeglut.h>

LIB_API Material::Material(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, float shininess) : Object{ name }, m_ambient{ ambient }, m_diffuse{ diffuse },
m_specular{ specular }, m_emission{ emission }, m_shininess{ shininess }, m_texture { nullptr } {};

LIB_API Material::~Material() {}


void LIB_API Material::apply() {
	// Set material properties:
	Shader* progShader = ShaderManager::getActiveShader();
	progShader->setVec3(progShader->getParamLocation("matEmission"), m_emission);
	progShader->setVec3(progShader->getParamLocation("matAmbient"), m_ambient);
	progShader->setVec3(progShader->getParamLocation("matDiffuse"), m_diffuse);
	progShader->setVec3(progShader->getParamLocation("matSpecular"), m_specular);
	progShader->setFloat(progShader->getParamLocation("matShininess"), m_shininess);
	/*progShader->setVec3(progShader->getParamLocation("matEmission"), glm::vec3(m_emission.x / 2, m_emission.y / 2, m_emission.z / 2));
	progShader->setVec3(progShader->getParamLocation("matAmbient"), glm::vec3(m_ambient.x / 2, m_ambient.y / 2, m_ambient.z / 2));
	progShader->setVec3(progShader->getParamLocation("matDiffuse"), glm::vec3(m_diffuse.x / 2, m_diffuse.y / 2, m_diffuse.z / 2));
	progShader->setVec3(progShader->getParamLocation("matSpecular"), glm::vec3(m_specular.x / 2, m_specular.y / 2, m_specular.z / 2));
	progShader->setFloat(progShader->getParamLocation("matShininess"), m_shininess/2);*/
	
	// Apply texture if present
	if (m_texture != nullptr) {
		m_texture->render(glm::mat4(1.0f));
	}
}

// GETTER + SETTERS

Texture LIB_API* Material::getTexture() const {
	return m_texture;
}

void LIB_API Material::setTexture(Texture* texture) {
	m_texture = texture;
}

glm::vec3 LIB_API Material::getAmbient() const {
	return m_diffuse;
}

glm::vec3 LIB_API Material::getDiffuse() const {
	return m_diffuse;
}

glm::vec3 LIB_API Material::getSpecular() const {
	return m_specular;
}

glm::vec3 LIB_API Material::getEmission() const {
	return m_emission;
}

float LIB_API Material::getShininess() const {
	return m_shininess;
}

void LIB_API Material::render(glm::mat4 coords)
{
}

