#pragma once
//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "node.h"
#include "cameraType.h"

	// C/C++
#include <string>

	// GLM:
#include <glm/glm.hpp>


/////////////
// CLASSES //
/////////////

/**
* Defines a generic camera.
*/
class LIB_API Camera : public Node {
protected:
	/**
	* Transformation matrix
	*/
	glm::mat4 m_properties;

	/**
	* Camera viewport width
	*/
	unsigned int m_width;

	/**
	* Camera viewport height
	*/
	unsigned int m_height;

	/**
	* Near plane
	*/
	float m_near;

	/**
	* Far plane
	*/
	float m_far;

	/**
	* Camera kind
	*/
	CameraType m_type;
public:

	/**
	* Constructor method
	*
	* \param type Camera type
	* \param name Node name
	* \param matrix Initial position relative to parent node
	* \param near Near plane
	* \param far Far plane
	* \param width Camera viewport width
	* \param height Camera viewport height
	*/
	Camera(CameraType type, const std::string& name, glm::mat4 matrix, float near, float far, unsigned int width, unsigned int height);

	/**
 * Get the near plane value.
 *
 * @return The near plane value.
 */
	float getNear() const;

	/**
	 * Get the far plane value.
	 *
	 * @return The far plane value.
	 */
	float getFar() const;

	/**
	 * Set a new near plane value.
	 *
	 * @param near The new near plane value.
	 */
	void setNear(float near);

	/**
	 * Set a new far plane value.
	 *
	 * @param far The new far plane value.
	 */
	void setFar(float far);

	/**
	 * Set a new viewport width.
	 *
	 * @param w The new viewport width.
	 */
	void setWidth(unsigned int w);

	/**
	 * Set a new viewport height.
	 *
	 * @param h The new viewport height.
	 */
	void setHeight(unsigned int h);

	/**
	 * Get the viewport width.
	 *
	 * @return The viewport width.
	 */
	unsigned int getWidth() const;

	/**
	 * Get the viewport height.
	 *
	 * @return The viewport height.
	 */
	unsigned int getHeight() const;

	/**
	 * Get the additional transform matrix (needed to alter camera location)
	 *
	 * @return The additional transform matrix.
	 */
	glm::mat4 getProperties();

	/**
	 * Render the object.
	 *
	 * @param transform The transform to apply to the object before rendering it.
	 */
	void virtual render(glm::mat4 transform) override = 0;

	/**
	 * Update the window size.
	 *
	 * @param width The new window width.
	 * @param height The new window height.
	 */
	void virtual updateWindowSize(unsigned int width, unsigned int height) = 0;

};
