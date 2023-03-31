#pragma once

#include "light.h"

/**
 * DirectionalLight class that describes a directional light source (aka infinite light).
 */
class LIB_API DirectionalLight : public Light {
public:
	/**
	 * Constructor method.
	 * 
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param ambient Ambient term vector
	 * \param diffuse Diffuse term vector
	 * \param specular Specular term vector
	 * \param direction Direction vector
	 */
	DirectionalLight(const std::string& name, glm::mat4 matrix, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);

	/**
	 * Render the light in the scene.
	 * 
	 * \param coords pre-computed world coordinates
	 */
	virtual void render(glm::mat4 coords) override;

private:
	glm::vec3 m_direction;
};