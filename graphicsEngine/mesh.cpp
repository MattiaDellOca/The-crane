#include "mesh.h"

//FreeGLUT:
	#include <GL/freeglut.h>

LIB_API Mesh::Mesh(std::string name, glm::mat4 matrix, Material material) : Node(name, matrix), m_material{ material } {};

const Material LIB_API& Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material material) {
	m_material = material;
}

void LIB_API Mesh::render(glm::mat4 matrix) {
	std::cout << "MESH: name: " << m_name << "id: " << m_id << std::endl;

	// Load material
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, powf(2.0f, 5));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_material.getAmbient()));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_material.getDiffuse()));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_material.getSpecular()));

	// Load matrix
	glLoadMatrixf(glm::value_ptr(m_matrix));
}