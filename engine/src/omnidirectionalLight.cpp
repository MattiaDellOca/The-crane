#include "omnidirectionalLight.h"
#include "shaderManager.h"

//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>


LIB_API OmnidirectionalLight::OmnidirectionalLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: PositionalLight(name, matrix, LightType::OMNIDIRECTIONAL, ambient, diffuse, specular, constantAttenuation,linearAttenuation, quadraticAttenuation)
{};


LIB_API void OmnidirectionalLight::render(glm::mat4 matrix)
{
	// Load light settings 
	glm::vec3 position = { matrix[3].x, matrix[3].y, matrix[3].z };
	/*Shader* progShader = ShaderManager::GetShader("programShader");
	progShader->setVec3(progShader->getParamLocation("lightPosition"), position);
	progShader->setVec3(progShader->getParamLocation("lightAmbient"), m_lightAmbient);
	progShader->setVec3(progShader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	progShader->setVec3(progShader->getParamLocation("lightSpecular"), m_lightSpecular);*/

}
