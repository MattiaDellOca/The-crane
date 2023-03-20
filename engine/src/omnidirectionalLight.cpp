#include "omnidirectionalLight.h"
#include "shaderWrapper.h"

//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>


LIB_API OmnidirectionalLight::OmnidirectionalLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: PositionalLight(name, matrix, LightType::OMNIDIRECTIONAL, ambient, diffuse, specular, constantAttenuation,linearAttenuation, quadraticAttenuation)
{};


LIB_API void OmnidirectionalLight::render(glm::mat4 matrix)
{
	//Position in (0,0,0) and the translation matrix will move the light
	//Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):

	//Values for omnidirectional light
	//glm::vec4 objectCoordPosition(0.f, 0.f, 0.f, 1.f); //w = 1
	//float cutoff = 180.f; //special value


	// Load modelview matrix
	glm::vec3 position = { matrix[3].x, matrix[3].y, matrix[3].z };
	ShaderWrapper::shader->setVec3(ShaderWrapper::shader->getParamLocation("lightPosition"), position);
	ShaderWrapper::shader->setVec3(ShaderWrapper::shader->getParamLocation("lightAmbient"), m_lightAmbient);
	ShaderWrapper::shader->setVec3(ShaderWrapper::shader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	ShaderWrapper::shader->setVec3(ShaderWrapper::shader->getParamLocation("lightSpecular"), m_lightSpecular);

	/*
	//Attenuation
	glLightf(m_baseValueLights + m_lightId, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
	glLightf(m_baseValueLights + m_lightId, GL_LINEAR_ATTENUATION, m_linearAttenuation);
	glLightf(m_baseValueLights + m_lightId, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);


	//Settings
	glLightfv(m_baseValueLights + m_lightId, GL_POSITION, glm::value_ptr(objectCoordPosition));
	glLightfv(m_baseValueLights + m_lightId, GL_SPOT_CUTOFF, &cutoff);

	glLightfv(m_baseValueLights + m_lightId, GL_AMBIENT, glm::value_ptr(m_lightAmbient));
	glLightfv(m_baseValueLights + m_lightId, GL_DIFFUSE, glm::value_ptr(m_lightDiffuse));
	glLightfv(m_baseValueLights + m_lightId, GL_SPECULAR, glm::value_ptr(m_lightSpecular));
	*/
}
