#include "light.h"


//Basic value for openGl Lights:
//GL_LIGHT0 = 0x4000
//GL_LIGHT5 = 0x4005
//LI_LIGHTX = 0x4000 + X
unsigned int Light::m_baseValueLights = 0x4000;


LIB_API Light::Light(std::string name, glm::mat4 matrix, LightType type, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node(name, matrix),
	m_type{type},
	m_lightId{lightId},
	m_lightAmbient{ ambient },
	m_lightDiffuse{ diffuse },
	m_lightSpecular{ specular }
{};