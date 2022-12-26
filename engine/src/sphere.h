#pragma once

#include "lib.h"
#include "mesh.h"

/**
 * Sphere class that describes a 3D sphere mesh.
 */
class LIB_API Sphere : public Mesh {
private:
	/**
	 * Radius of the sphere.
	 */
	float m_radius;
public:
	/**
	 * Constructor method.
	 * 
	 * \param radius Radius of the sphere
	 * \param name Node name
	 * \param matrix Transformation matrix
	 * \param material Pointer to a material object
	 */
	Sphere(float radius, std::string name, glm::mat4 matrix, Material *material);

	/**
	 * Renders the sphere to screen.
	 * 
	 * \param coords Pre-computed world coordinates
	 */
	void render(glm::mat4 coords);
};