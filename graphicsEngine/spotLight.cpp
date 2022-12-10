#include "spotLight.h"

LIB_API SpotLight::SpotLight(std::string name, glm::mat4 matrix, unsigned int lightId, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float cutoff)
	: Light(name, matrix, LightType::SPOT, lightId, ambient, diffuse, specular) {
	if (cutoff >= 0 && cutoff <= 90) {
		m_cutoff = cutoff;
	}
	else {
		//throw exception
	}
};


LIB_API void SpotLight::render(glm::mat4)
{
	//Position in (0,0,0) and the translation matrix will move the light

	//Values for omnidirectional light
	glm::vec4 position(0.f, 0.f, 0.f, 1.f); //w = 1

	//rendering
	std::cout << "DirectionalLight" << std::endl;
}
