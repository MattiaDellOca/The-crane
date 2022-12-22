#pragma once

#include "lib.h"
#include "mesh.h"

/**
 * Cube class that describes a 3D Cube mesh.
 */
class LIB_API Cube : public Mesh {
private:
	/**
	 * Cube edge length.
	 */
	float m_edge;
public:
	/**
	 * Constructor method.
	 * 
	 * \param edge Cube edge length
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param material Pointer to a Material object
	 */
	Cube(float edge, std::string name, glm::mat4 matrix, Material *material);

	/**
	 * Renders the cube to the screen.
	 * 
	 * \param coords pre-computed world coordinates
	 */
	void render(glm::mat4 coords);
};