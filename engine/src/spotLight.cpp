#include "spotLight.h"
#include <stdexcept>
//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>


LIB_API SpotLight::SpotLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutoff, glm::vec3 direction, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: PositionalLight(name, matrix, LightType::SPOT, ambient, diffuse, specular, constantAttenuation, linearAttenuation, quadraticAttenuation), m_direction{ direction } {
	if (cutoff >= 0 && cutoff <= 90) {
		m_cutoff = cutoff;
	}
	else {
		//the light is created and the light id is incremented, it's needed to decrement it
		m_incrementalLightId--;
		//throw exception
		throw std::invalid_argument("Cutoff angle error: " + name);
	}
};


LIB_API void SpotLight::render(glm::mat4 matrix)
{
	//Position in (0,0,0) and the translation matrix will move the light
	//Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):

	//Values for omnidirectional light
	glm::vec4 objectCoordPosition(0.f, 0.f, 0.f, 1.f); //w = 1

	//Load matrix
	/*
	glLoadMatrixf(glm::value_ptr(matrix));

	//Attenuation
	glLightf(m_baseValueLights + m_lightId, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
	glLightf(m_baseValueLights + m_lightId, GL_LINEAR_ATTENUATION, m_linearAttenuation);
	glLightf(m_baseValueLights + m_lightId, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);

	//Settings
	glLightfv(m_baseValueLights + m_lightId, GL_POSITION, glm::value_ptr(objectCoordPosition));
	glLightfv(m_baseValueLights + m_lightId, GL_SPOT_CUTOFF, &m_cutoff);
	glLightfv(m_baseValueLights + m_lightId, GL_SPOT_DIRECTION, glm::value_ptr(m_direction));

	glLightfv(m_baseValueLights + m_lightId, GL_AMBIENT, glm::value_ptr(m_lightAmbient));
	glLightfv(m_baseValueLights + m_lightId, GL_DIFFUSE, glm::value_ptr(m_lightDiffuse));
	glLightfv(m_baseValueLights + m_lightId, GL_SPECULAR, glm::value_ptr(m_lightSpecular));
	*/
}
