#pragma once

#include "positionalLight.h"

/**
 * OmnidirectionalLight class that describes an omnidirectional (positional) light source (aka point light).
 */
class LIB_API OmnidirectionalLight : public PositionalLight {
public:
	/**
	 * Constructor method.
	 * 
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param ambient Ambient term vector
	 * \param diffuse Diffuse term vector
	 * \param specular Specular term vector
	 * \param constantAttenuation Constant attenuation term
	 * \param linearAttenuation Linear attenuation term
	 * \param quadraticAttenuation Quadratic attenuation term
	 */
	OmnidirectionalLight(const std::string& name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float constantAttenuation = 1.f, float linearAttenuation = 0.f, float quadraticAttenuation = 0.f);
	
	/**
	 * Renders the omnidirectional light in the scene.
	 * 
	 * \param coords Pre-computed world coordinates
	 */
	virtual void render(glm::mat4 coords) override;
};