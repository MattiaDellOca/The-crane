
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
	ShaderManager::GetShader("programShader")->setVec3(ShaderManager::GetShader("programShader")->getParamLocation("matEmission"), m_emission);
	ShaderManager::GetShader("programShader")->setVec3(ShaderManager::GetShader("programShader")->getParamLocation("matAmbient"), m_ambient);
	ShaderManager::GetShader("programShader")->setVec3(ShaderManager::GetShader("programShader")->getParamLocation("matDiffuse"), m_diffuse);
	ShaderManager::GetShader("programShader")->setVec3(ShaderManager::GetShader("programShader")->getParamLocation("matSpecular"), m_specular);
	ShaderManager::GetShader("programShader")->setFloat(ShaderManager::GetShader("programShader")->getParamLocation("matShininess"), m_shininess);


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

