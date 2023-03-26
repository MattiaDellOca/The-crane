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
	Shader* progShader = ShaderManager::GetShader("programShaderDirectionalLight");
	progShader->setVec3(progShader->getParamLocation("lightDirection"), m_direction);
	progShader->setVec3(progShader->getParamLocation("lightAmbient"), m_lightAmbient);
	progShader->setVec3(progShader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	progShader->setVec3(progShader->getParamLocation("lightSpecular"), m_lightSpecular);
}
