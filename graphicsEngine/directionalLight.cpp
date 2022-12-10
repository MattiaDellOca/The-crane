#include "directionalLight.h"

LIB_API DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Light(name, matrix, LightType::DIRECTIONAL, lightId, ambient, diffuse, specular) {};


LIB_API void DirectionalLight::render(glm::mat4)
{
	//Position in (0,0,0) and the translation matrix will move the light
	
	//Values for omnidirectional light
	glm::vec4 position(0.f, 0.f, 0.f, 0.f); //w = 0

	//rendering
	std::cout << "DirectionalLight" << std::endl;
}
