#include "spotLight.h"
#include "shaderManager.h"

#include <stdexcept>
//FreeGLUT:
#include <GL/freeglut.h>

//GLM:
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


LIB_API SpotLight::SpotLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutoff, glm::vec3 direction, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
	: PositionalLight(name, matrix, LightType::SPOT, ambient, diffuse, specular, constantAttenuation, linearAttenuation, quadraticAttenuation), m_direction{ direction } {
	if (cutoff >= 0 && cutoff <= 90) {
		m_cutoff = cutoff;
	}
	else {
		//the light is created and the light id is incremented, it's needed to decrement it
		m_incrementalLightId--;
		//throw exception
		throw std::invalid_argument("Cutoff angle error: " + name);
	}
};


LIB_API void SpotLight::render(glm::mat4 matrix)
{
	glm::vec3 position = { matrix[3].x, matrix[3].y, matrix[3].z };
	glm::vec4 direction = matrix * glm::vec4(m_direction, 0.0f);

	Shader* progShader = ShaderManager::getShader("programShaderSpotLight");
	progShader->setVec3(progShader->getParamLocation("lightPosition"), position);
	progShader->setVec3(progShader->getParamLocation("lightAmbient"), m_lightAmbient);
	progShader->setVec3(progShader->getParamLocation("lightDiffuse"), m_lightDiffuse);
	progShader->setVec3(progShader->getParamLocation("lightSpecular"), m_lightSpecular);
	progShader->setVec3(progShader->getParamLocation("lightDirection"), glm::vec3(direction.x, direction.y, direction.z));
	progShader->setFloat(progShader->getParamLocation("lightCutoff"), m_cutoff);
	progShader->setFloat(progShader->getParamLocation("lightExponent"), m_linearAttenuation);
}
