#include "mesh.h"


// GLEW
#include <GL/glew.h>

//FreeGLUT:
#include <GL/freeglut.h>



LIB_API Mesh::Mesh(const std::string& name, glm::mat4 matrix, Material* material, bool m_cast_shadows) : Node(name, matrix), m_material{ material }, m_faces{ 0 }, m_cast_shadows{ m_cast_shadows } {};

LIB_API Mesh::~Mesh(){
	for (auto v : m_vertices)
		delete v;

	glDeleteBuffers(1, &m_vertex_vbo);
	glDeleteBuffers(1, &m_normal_vbo);
	glDeleteBuffers(1, &m_texture_vbo);
	glDeleteBuffers(1, &m_face_index_vbo);

	glDeleteVertexArrays(1, &m_vao);
}

const Material LIB_API *Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material *material) {
	m_material = material;
}

void LIB_API Mesh::setNFaces(unsigned int nFaces) {
	m_faces = nFaces;
}

void LIB_API Mesh::setVertexVbo(unsigned int vertexVbo) {
	m_vertex_vbo = vertexVbo;
}

void LIB_API Mesh::setNormalVbo(unsigned int normalVbo) {
	m_normal_vbo = normalVbo;
}

void LIB_API Mesh::setTextureVbo(unsigned int textureVbo) {
	m_texture_vbo = textureVbo;
}

void LIB_API Mesh::setFaceIndexVbo(unsigned int faceIndexVbo) {
	m_face_index_vbo = faceIndexVbo;
}

void LIB_API Mesh::setVao(unsigned int vao) {
	m_vao = vao;
}

void LIB_API Mesh::render(glm::mat4 matrix) {
	// Load material
	m_material->apply();

	// Check if a texture has been set
	if (m_material->getTexture() != nullptr) {
		glEnable(GL_TEXTURE_2D);
	}

	// Load matrix
	glLoadMatrixf(glm::value_ptr(matrix));

	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_normal_vbo);
	glNormalPointer(GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
	glTexCoordPointer(2, GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_face_index_vbo);
	glDrawElements(GL_TRIANGLES, m_faces * 3, GL_UNSIGNED_INT, nullptr);
	
	/*
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_faces * 3, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	*/

	// Check if a texture has been set
	if (m_material->getTexture() != nullptr) {
		glDisable(GL_TEXTURE_2D);
	}
}

void LIB_API Mesh::renderShadow(glm::mat4 cameraInv, glm::mat4 parentRelativeCoords) {
	// Change depth function to avoid Z-fighting
	glDepthFunc(GL_LEQUAL);

	// Create projection matrix onto xz plane
	glm::mat4 projectionXZ(
		1.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	// Now, compute shadowCastMatrix.
	// Operations:
	// 1. Flat mesh
	// 2. Add transformations
	// 3. Project all points to XZ plane
	// 4. Translate up to avoid z-fighting
	glm::mat4 shadowCastMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, .7f, 0.f)) * projectionXZ * parentRelativeCoords * glm::scale(glm::mat4(1.f), glm::vec3(1.f, 0.f, 1.f));
	glm::vec3 planeNormal(0.f, 1.f, 0.f);

	// Set shadow material
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
	
	// Compute + load world coordinate 
	glLoadMatrixf(glm::value_ptr(cameraInv * shadowCastMatrix));

	// Draw shadow for each face composing the mesh
	for (int i = 0; static_cast<unsigned int>(i) < m_faces; i++) {
		// Load the three vertices composing a face
		Vertex* v1 = m_vertices.at(i * 3);
		Vertex* v2 = m_vertices.at(i * 3 + 1);
		Vertex* v3 = m_vertices.at(i * 3 + 2);

		// Draw face flat on y=0
		glBegin(GL_TRIANGLES);

		// Scalar distance + distance point * plane
		glNormal3fv(glm::value_ptr(planeNormal));
		glVertex3fv(glm::value_ptr(v1->getPosition()));

		glNormal3fv(glm::value_ptr(planeNormal));
		glVertex3fv(glm::value_ptr(v2->getPosition()));

		glNormal3fv(glm::value_ptr(planeNormal));
		glVertex3fv(glm::value_ptr(v3->getPosition()));
		glEnd();
	}

	// Reset
	glDepthFunc(GL_LESS);
}

// Add one face to the mesh: a face is represented by three vertices.
// Given the i-th face, it will be composed by vertices in i, i+1 and i+2 position in the vertices vector
void LIB_API Mesh::addFace(Vertex* v1, Vertex* v2, Vertex* v3) {
	m_vertices.push_back(v1);
	m_vertices.push_back(v2);
	m_vertices.push_back(v3);
	m_faces++;
}

void LIB_API Mesh::setShadowCast(bool enabled) {
	this->m_cast_shadows = enabled;
}

bool LIB_API Mesh::isShadowCastEnabled() const {
	return this->m_cast_shadows;
}
