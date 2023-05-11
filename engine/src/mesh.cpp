#include "mesh.h"
#include "engine.h"
#include "shaderManager.h"

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

	// Load modelview matrix
	Shader* progShader = ShaderManager::getActiveShader();
	progShader->setMatrix(progShader->getParamLocation("modelview"), matrix);

	// Load inverse-transpose matrix
	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(matrix));
	progShader->setMatrix3(progShader->getParamLocation("normalMatrix"), normalMatrix);


	// Render the mesh using VAO
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_faces * 3, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
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
	glm::mat4 shadowCastMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, .1f, 0.f)) * projectionXZ * parentRelativeCoords * glm::scale(glm::mat4(1.f), glm::vec3(1.f, 0.f, 1.f));

	// Set shadow material
	Shader* progShader = ShaderManager::getActiveShader();
	progShader->setVec3(progShader->getParamLocation("matEmission"), glm::vec3(0.f, 0.f, 0.f));
	progShader->setVec3(progShader->getParamLocation("matAmbient"), glm::vec3(0.0f, 0.0f, 0.0f));
	progShader->setVec3(progShader->getParamLocation("matDiffuse"), glm::vec3(0.0f, 0.0f, 0.0f));
	progShader->setVec3(progShader->getParamLocation("matSpecular"), glm::vec3(0.0f, 0.0f, 0.0f));
	progShader->setFloat(progShader->getParamLocation("matShininess"), 0.0f);
	
	// Load modelview matrix
	progShader->setMatrix(progShader->getParamLocation("modelview"), cameraInv * shadowCastMatrix);

	// Load inverse-transpose matrix
	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	progShader->setMatrix3(progShader->getParamLocation("normalMatrix"), normalMatrix);

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
