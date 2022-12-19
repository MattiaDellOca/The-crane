#include "mesh.h"

//FreeGLUT:
	#include <GL/freeglut.h>


LIB_API Mesh::Mesh(std::string name, glm::mat4 matrix, Material* material) : Node(name, matrix), m_material{ material }, m_vertices{ nullptr } {};

const Material LIB_API *Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material *material) {
	m_material = material;
}

void LIB_API Mesh::render(glm::mat4 matrix) {
	std::cout << "MESH: name: " << m_name << "id: " << m_id << std::endl;
	std::cout << "\tLoading " << m_vertices->size() << " vertices" << std::endl;

	// Load material
	m_material->apply();

	// Load matrix
	glLoadMatrixf(glm::value_ptr(m_matrix));

	glBegin(GL_TRIANGLES);
	for (auto* v : *m_vertices) {
		glNormal3fv(glm::value_ptr(v->getNormal()));
		glTexCoord2fv(glm::value_ptr(v->getTexture()));
		glVertex3fv(glm::value_ptr(v->getPosition()));
	}
	glEnd();
}

void LIB_API Mesh::addVertex(Vertex* vertex) {
	// Initialize vecor if null
	if (m_vertices == nullptr)
		m_vertices = new std::vector<Vertex*>();
	m_vertices->push_back(vertex);
}