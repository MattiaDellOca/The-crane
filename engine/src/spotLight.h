#pragma once

#include "positionalLight.h"

/**
 * SpotLight class that describes a spotlight (positional) light source.
 */
class LIB_API SpotLight : public PositionalLight {
private:
	/**
	 * Cut off angle. Allowed any angle between 0° and 90°
	 */
	float m_cutoff;

	/**
	 * Spotlight direction vector.
	 */
	glm::vec3 m_direction;

public:

	/**
	 * Constructor method.
	 * 
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param ambient Ambient term
	 * \param diffuse Diffuse term
	 * \param specular Specular term
	 * \param cutoff Cutoff angle
	 * \param direction Spotlight direction vector
	 * \param constantAttenuation Constant attenuation term
	 * \param linearAttenuation Linear attenuation term
	 * \param quadraticAttenuation Quadratic attenuation term
	 */
	SpotLight(std::string name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float cutoff, glm::vec3 direction, float constantAttenuation = 1.f, float linearAttenuation = 0.f, float quadraticAttenuation = 0.f);

	/**
	 * Renders spot light in scene.
	 * 
	 * \param coords Pre-computed world coordinates
	 */
	virtual void render(glm::mat4 coords);
};