#include "sphere.h"

//FreeGLUT:
#include <GL/freeglut.h>

LIB_API Sphere::Sphere(float radius, std::string name, glm::mat4 matrix, Material material) : Mesh(name, matrix, material), m_radius{ radius } {};

void LIB_API Sphere::render(glm::mat4) {

	// Render sphere
	std::cout << "SPHERE: radius: " << m_radius << " Name: " << m_name << std::endl;
	glutSolidSphere(m_radius, (int)8 * 5, (int)8 * 5);
}