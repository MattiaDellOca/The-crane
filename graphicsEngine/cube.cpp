#include "cube.h"

	//FreeGLUT:
#include <GL/freeglut.h>

   //GLM:
#include <glm/gtc/type_ptr.hpp>

LIB_API Cube::Cube(float edge, std::string name, glm::mat4 matrix, Material *material) : Mesh{ name,matrix, material }, m_edge{edge} {};

void LIB_API Cube::render(glm::mat4 coords) {
	glEnable(GL_TEXTURE_2D);

	// Load matrix
	glLoadMatrixf(glm::value_ptr(coords));

	// FIXME: Load material
	m_material->apply();
	glutSolidCube(m_edge);
}