#include "omnidirectionalLight.h"

//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>


LIB_API OmnidirectionalLight::OmnidirectionalLight(std::string name, glm::mat4 matrix, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Light(name, matrix, LightType::OMNIDIRECTIONAL, lightId, ambient, diffuse, specular) {};


LIB_API void OmnidirectionalLight::render(glm::mat4 matrix)
{
	//Position in (0,0,0) and the translation matrix will move the light
	//Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):

	//Values for omnidirectional light
	glm::vec4 objectCoordPosition(0.f, 0.f, 0.f, 1.f); //w = 1
	float cutoff = 180.f; //special value

	//rendering
	std::cout << "DirectionalLight " << m_type << std::endl;

	//Load matrix
	glLoadMatrixf(glm::value_ptr(matrix));

	//Settings
	glLightfv(m_baseValueLights + m_lightId, GL_POSITION, glm::value_ptr(objectCoordPosition));
	glLightfv(m_baseValueLights + m_lightId, GL_SPOT_CUTOFF, &cutoff);

	glLightfv(m_baseValueLights + m_lightId, GL_AMBIENT, glm::value_ptr(m_lightAmbient));
	glLightfv(m_baseValueLights + m_lightId, GL_DIFFUSE, glm::value_ptr(m_lightDiffuse));
	glLightfv(m_baseValueLights + m_lightId, GL_SPECULAR, glm::value_ptr(m_lightSpecular));

}
