#pragma once

#include "light.h"

/**
 * PositionalLight abstract class that describes a light source with light attenuation features.
 */
class LIB_API PositionalLight : public Light {
protected:
	/**
	 * Constrant attenuation term.
	 */
	float m_constantAttenuation;

	/**
	 * Linear attenuation term.
	 */
	float m_linearAttenuation;

	/**
	 * Quadratic attenuation term.
	 */
	float m_quadraticAttenuation;

	/**
	 * Constructor method.
	 * 
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param type Light type
	 * \param ambient Ambient term 
	 * \param diffuse Diffuse term
	 * \param specular Specular term
	 * \param constantAttenuation Constant attenuation term
	 * \param linearAttenuation Linear attenuation term
	 * \param quadraticAttenuation Quadratic attenuation term
	 */
	PositionalLight(const std::string& name, glm::mat4 matrix, LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constantAttenuation = 1.f, float linearAttenuation = 0.f,float quadraticAttenuation = 0.f);
public: 

	/**
	 * Abstract render method.
	 * 
	 * \param coords Pre-computed world coordinate
	 */
	virtual void render(glm::mat4 coords) override = 0;
};