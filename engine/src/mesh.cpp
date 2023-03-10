#include "mesh.h"


// GLEW
#include <GL/glew.h>

//FreeGLUT:
#include <GL/freeglut.h>


LIB_API Mesh::Mesh(const std::string& name, glm::mat4 matrix, unsigned int faces, unsigned int vertexVbo, unsigned int normalVbo, unsigned int textureVbo, unsigned int faceIndexVbo, unsigned int vao, Material* material, bool cast_shadows)
	: Node(name, matrix), m_material{ material }, m_cast_shadows{ cast_shadows }, m_faces{ faces }, m_vertex_vbo{ vertexVbo }, m_normal_vbo{ normalVbo }, m_texture_vbo{ textureVbo }, m_face_index_vbo{ faceIndexVbo }, m_vao{ vao } {};

LIB_API Mesh::~Mesh(){
	glDeleteBuffers(1, &m_vertex_vbo);
	glDeleteBuffers(1, &m_normal_vbo);
	glDeleteBuffers(1, &m_texture_vbo);
	glDeleteBuffers(1, &m_face_index_vbo);

	glDeleteVertexArrays(1, &m_vao);
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
	
	// Render the mesh using VAO
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_faces * 3, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	

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

	// Set shadow material
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec3(0.05f, 0.05f, 0.05f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
	
	// Compute + load world coordinate 
	glLoadMatrixf(glm::value_ptr(cameraInv * shadowCastMatrix));

	// Render the mesh using VAO
	// Warning: the VAO contains a VBO for rendering texture, but the shadows consist of a complete black color, therefore the texture are applied but not seen
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_faces * 3, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	
	// Reset
	glDepthFunc(GL_LESS);
}

void LIB_API Mesh::setShadowCast(bool enabled) {
	this->m_cast_shadows = enabled;
}

bool LIB_API Mesh::isShadowCastEnabled() const {
	return this->m_cast_shadows;
}
