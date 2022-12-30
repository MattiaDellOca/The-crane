#include "mesh.h"

//FreeGLUT:
	#include <GL/freeglut.h>


LIB_API Mesh::Mesh(std::string name, glm::mat4 matrix, Material* material) : Node(name, matrix), m_material{ material }, m_faces{ 0 } {};

const Material LIB_API *Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material *material) {
	m_material = material;
}

void LIB_API Mesh::render(glm::mat4 matrix) {
	if (m_name == "Hook" || m_name == "Container1" || m_name == "Container2") {
		//std::cout << m_name << glm::to_string(matrix) << std::endl;
	}

	// Load material
	m_material->apply();

	// Check if a texture has been set
	if (m_material->getTexture() != nullptr) {
		glEnable(GL_TEXTURE_2D);
	}

	// Load matrix
	glLoadMatrixf(glm::value_ptr(matrix));

	// Load each face composing the mesh
	for (int i = 0; static_cast<unsigned int>(i) < m_faces; i++) {
		// Load the three vertices composing a face
		Vertex* v1 = m_vertices.at(i * 3);
		Vertex* v2 = m_vertices.at(i * 3 + 1);
		Vertex* v3 = m_vertices.at(i * 3 + 2);

		// Draw face
		glBegin(GL_TRIANGLES);
			glNormal3fv(glm::value_ptr(v1->getNormal()));
			glTexCoord2fv(glm::value_ptr(v1->getTexture()));
			glVertex3fv(glm::value_ptr(v1->getPosition()));

			glNormal3fv(glm::value_ptr(v2->getNormal()));
			glTexCoord2fv(glm::value_ptr(v2->getTexture()));
			glVertex3fv(glm::value_ptr(v2->getPosition()));

			glNormal3fv(glm::value_ptr(v3->getNormal()));
			glTexCoord2fv(glm::value_ptr(v3->getTexture()));
			glVertex3fv(glm::value_ptr(v3->getPosition()));
		glEnd();
	}

	// Check if a texture has been set
	if (m_material->getTexture() != nullptr) {
		glDisable(GL_TEXTURE_2D);
	}
}

// Add one face to the mesh: a face is represented by three vertices.
// Given the i-th face, it will be composed by vertices in i, i+1 and i+2 position in the vertices vector
void LIB_API Mesh::addFace(Vertex* v1, Vertex* v2, Vertex* v3) {
	m_vertices.push_back(v1);
	m_vertices.push_back(v2);
	m_vertices.push_back(v3);
	m_faces++;
}