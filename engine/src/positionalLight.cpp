#include "positionalLight.h"

LIB_API PositionalLight::PositionalLight(const std::string& name, glm::mat4 matrix, LightType type, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: Light(name, matrix, type, ambient, diffuse, specular),m_constantAttenuation{constantAttenuation}, m_linearAttenuation{linearAttenuation}, m_quadraticAttenuation{quadraticAttenuation}
{};
