#include "directionalLight.h"
#include "shaderManager.h"

//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>


LIB_API DirectionalLight::DirectionalLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
	: Light(name, matrix, LightType::DIRECTIONAL, ambient, diffuse, specular), m_direction{ direction }
{};


LIB_API void DirectionalLight::render(glm::mat4 matrix)
{
	// Calculate the direction
	glm::vec4 direction = matrix * glm::vec4(m_direction, 0.0f);
	Shader* progShader = ShaderManager::getShader("programShaderDirectionalLight");
	progShader->setVec3(progShader->getParamLocation("lightDirection"), glm::vec3(direction.x, direction.y, direction.z));
	progShader->setVec3(progShader->getParamLocation("lightAmbient"), m_lightAmbient);
	progShader->setVec3(progShader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	progShader->setVec3(progShader->getParamLocation("lightSpecular"), m_lightSpecular);
}