#include "directionalLight.h"

LIB_API DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Light(name, matrix, LightType::DIRECTIONAL, lightId, ambient, diffuse, specular) {};

LIB_API void DirectionalLight::render(glm::mat4)
{
	std::cout << "DirectionalLight" << std::endl;
}
