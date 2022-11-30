#include "sphere.h"

//GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


   //FreeGLUT:
#include <GL/freeglut.h>


LIB_API Sphere::Sphere(int radius, glm::mat4 matrix, std::string name) : Node(name, matrix), m_radius{ radius } {};

void LIB_API Sphere::render() {
	// Render sphere
	std::cout << "SPHERE!" << std::endl;

	// Display sphere
	glLoadMatrixf(glm::value_ptr(m_matrix));
	glutSolidSphere(1, (int)8 * 5, (int)8 * 5);

	// Call render children
	Node::render();
}