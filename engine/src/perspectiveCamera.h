#pragma once
//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "camera.h"

	// C/C++
#include <string>

	// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/////////////
// CLASSES //
/////////////


/**
 * Class that describes a perspective camera.
 */
class LIB_API PerspectiveCamera : public Camera {
private:
	/**
	 * FOV (Field Of View) of the camera.
	 */
	float m_fov;
public:
	/**
	 * Constructor method.
	 *
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param width Width of the camera viewport
	 * \param height Height of the camera viewport
	 * \param near Near plane
	 * \param far Far plane
	 * \param fov Field of view of the camera
	 */
	PerspectiveCamera(const std::string& name, glm::mat4 matrix, unsigned int width, unsigned int height, float near, float far, float fov = 45.0f);

	/**
	 * Render method to render the camera.
	 *
	 * \param matrix projection matrix
	 */
	virtual void render(glm::mat4 matrix) override;

	/**
	 * Updates the current perspective matrix using new width and height.
	 *
	 * \param width New width of the viewport
	 * \param height New height of the viewport
	 */
	virtual void updateWindowSize(unsigned int width, unsigned int height) override;

	/**
	 * Sets the position matrix of the camera.
	 *
	 * \param posMatrix New position matrix
	 */
	void setPositionMatrix(glm::mat4 posMatrix);

	void setPropertiesMatrix(glm::mat4 propertiesMatrix);
};
