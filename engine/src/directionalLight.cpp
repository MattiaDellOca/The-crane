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
	//Position in (0,0,0) and the translation matrix will move the light
	//Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):

	//Values for omnidirectional light
	//glm::vec4 objectCoordPosition(0.f, 0.f, 0.f, 0.f); //w = 0


	Shader* progShader = ShaderManager::GetShader("programShaderDirectionalLight");
	progShader->setVec3(progShader->getParamLocation("lightDirection"), m_direction);
	progShader->setVec3(progShader->getParamLocation("lightAmbient"), m_lightAmbient);
	progShader->setVec3(progShader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	progShader->setVec3(progShader->getParamLocation("lightSpecular"), m_lightSpecular);
	
	



	//Reset attenuation

	/*
	glLightf(m_baseValueLights + m_lightId, GL_CONSTANT_ATTENUATION, 1.f);
	glLightf(m_baseValueLights + m_lightId, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(m_baseValueLights + m_lightId, GL_QUADRATIC_ATTENUATION, 0.f);


	//Load matrix
	glLoadMatrixf(glm::value_ptr(matrix));

	//Settings
	glLightfv(m_baseValueLights + m_lightId, GL_POSITION, glm::value_ptr(objectCoordPosition));

	glLightfv(m_baseValueLights + m_lightId, GL_AMBIENT, glm::value_ptr(m_lightAmbient));
	glLightfv(m_baseValueLights + m_lightId, GL_DIFFUSE, glm::value_ptr(m_lightDiffuse));
	glLightfv(m_baseValueLights + m_lightId, GL_SPECULAR, glm::value_ptr(m_lightSpecular));
	*/
}
