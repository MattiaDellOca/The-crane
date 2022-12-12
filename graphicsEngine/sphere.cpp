#include "sphere.h"

//FreeGLUT:
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>


LIB_API Sphere::Sphere(float radius, std::string name, glm::mat4 matrix, Material material) : Mesh(name, matrix, material), m_radius{ radius } {};

void LIB_API Sphere::render(glm::mat4 matrix) {

		
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_material.getShininess());
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_material.getAmbient()));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_material.getDiffuse()));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_material.getSpecular()));

	//Load matrix
	glLoadMatrixf(glm::value_ptr(matrix));

	// Render sphere
	std::cout << "SPHERE: radius: " << m_radius << " Name: " << m_name << std::endl;
	glutSolidSphere(m_radius, (int)8 * 5, (int)8 * 5);
}