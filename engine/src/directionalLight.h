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
	 */
	DirectionalLight(std::string name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);

	/**
	 * Render the light in the scene.
	 * 
	 * \param coords pre-computed world coordinates
	 */
	virtual void render(glm::mat4 coords);
};