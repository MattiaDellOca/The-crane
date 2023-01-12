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
 * Class that describes an orthographic camera.
 */
class LIB_API OrthographicCamera : public Camera {
public:
	/**
	 * Constructor method.
	 * 
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param width Width of the viewport of the camera
	 * \param height Height of the viewport of the camera
	 */
	OrthographicCamera(std::string name, glm::mat4 matrix, unsigned int width, unsigned int height);

	/**
	 * Render method used to render the camera.
	 * 
	 * \param matrix projection matrix
	 */
	virtual void render(glm::mat4 matrix) override;

	/**
	 * Updates the current orthographic matrix using new width and height.
	 * 
	 * \param width New width of the viewport
	 * \param height New height of the viewport
	 */
	virtual void updateWindowSize(unsigned int width, unsigned int height) override;
};
