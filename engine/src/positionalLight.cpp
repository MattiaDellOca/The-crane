#include "positionalLight.h"

LIB_API PositionalLight::PositionalLight(const std::string& name, glm::mat4 matrix, LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: Light(name, matrix, type, ambient, diffuse, specular),m_constantAttenuation{constantAttenuation}, m_linearAttenuation{linearAttenuation}, m_quadraticAttenuation{quadraticAttenuation}
{};
