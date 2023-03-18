#include "light.h"

#include <stdexcept>
//FreeGLUT:
#include <GL/freeglut.h>

//Basic value for openGl Lights:
//GL_LIGHT0 = 0x4000
//GL_LIGHT5 = 0x4005
//LI_LIGHTX = 0x4000 + X
unsigned int Light::m_baseValueLights = GL_LIGHT0;

//Incremental value used in openGL for identify the light
unsigned int Light::m_incrementalLightId = 0;
int Light::m_maxLights = 0;

LIB_API Light::Light(const std::string& name, glm::mat4 matrix, LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: Node(name, matrix),
	m_type{type},
	m_lightId{ m_incrementalLightId },
	m_lightAmbient{ ambient },
	m_lightDiffuse{ diffuse },
	m_lightSpecular{ specular }
	{
		//The first time a light is instantiated the max lights is calculated
		if (m_incrementalLightId == 0) {
			glGetIntegerv(GL_MAX_LIGHTS, &m_maxLights);
		}
		//Throw an exception if opengl can't manage the light
		else if (m_incrementalLightId > size_t(m_maxLights - 1)) {
			throw std::runtime_error("Maximum number of lights possible reached: " + name);
		}

		//increment lightid
		m_incrementalLightId++;
		//enable light
		//glEnable(m_baseValueLights + m_lightId);
	};


const LIB_API unsigned int& Light::getLightId() {
	return m_lightId;
}

const LIB_API LightType& Light::getLightType()
{
	return m_type;
}