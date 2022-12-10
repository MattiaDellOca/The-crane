#include "light.h"

LIB_API Light::Light(std::string name, glm::mat4 matrix, LightType type, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node(name, matrix),
	m_type{type},
	m_lightId{lightId},
	m_lightAmbient{ ambient },
	m_lightDiffuse{ diffuse },
	m_lightSpecular{ specular }
{	
	std::cout << "Light" << m_lightId << std::endl;
};