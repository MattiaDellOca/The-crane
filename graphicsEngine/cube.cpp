#include "cube.h"

//FreeGLUT:
#include <GL/freeglut.h>

LIB_API Cube::Cube(float edge, std::string name, glm::mat4 matrix, Material *material) : Mesh{ name,matrix, material }, m_edge{edge} {};

void LIB_API Cube::render(glm::mat4 coords) {
	// Render cube
	std::cout << "CUBE: edge: " << m_edge << " Name: " << m_name << std::endl;

	// Load superclass
	Mesh::render(coords);

	// Show cube
	glutSolidCube(m_edge);
}