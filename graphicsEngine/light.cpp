#include "light.h"

LIB_API Light::Light(std::string name, glm::mat4 matrix, LightType type, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node(name, matrix),
	m_type{type},
	m_lightId{lightId},
	m_lightPosition{glm::vec3(0.f,0.f,0.f)},
	m_lightAmbient{ ambient },
	m_lightDiffuse{ diffuse },
	m_lightSpecular{ specular }
{
	std::cout << "Light" << m_lightId << std::endl;
};


//Factory method
/*
Light LIB_API Light::create(std::string name, glm::mat4 matrix, LightType type, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular) {
	return Light(name, matrix, type, lightId, ambient, diffuse, specular);
}*/

/*
void LIB_API Light::render(glm::mat4 matrix) {
	std::cout << "Light: name: " << m_name << std::endl;

	// Render light

}*/