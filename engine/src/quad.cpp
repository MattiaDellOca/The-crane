// Header:
#include "quad.h"

// Glew:
#include <GL/glew.h>

/**
 * Constructor.
 */
LIB_API Quad::Quad(const std::string& name, unsigned int windowSizeX, unsigned int windowSizeY) : Object(name), m_window_size_x { windowSizeX }, m_window_size_y { windowSizeY } {
	createPlane();
}

/**
 * Destructor.
 */
LIB_API Quad::~Quad() {
	glDeleteBuffers(1, &m_vertex_vbo);
	glDeleteBuffers(1, &m_texture_vbo);
}

void LIB_API Quad::createPlane() {
	// Generate VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create a 2D box for screen rendering:
	glm::vec2* boxPlane = new glm::vec2[4];
	boxPlane[0] = glm::vec2(0.0f, 0.0f);
	boxPlane[1] = glm::vec2(m_window_size_x / 2.0f, 0.0f);
	boxPlane[2] = glm::vec2(0.0f, m_window_size_y);
	boxPlane[3] = glm::vec2(m_window_size_x / 2.0f, m_window_size_y);

	// Copy data into VBO:
	glGenBuffers(1, &m_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), boxPlane, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	delete[] boxPlane;

	// Set texture coordinates:
	glm::vec2* texCoord = new glm::vec2[4];
	texCoord[0] = glm::vec2(0.0f, 0.0f);
	texCoord[1] = glm::vec2(1.0f, 0.0f);
	texCoord[2] = glm::vec2(0.0f, 1.0f);
	texCoord[3] = glm::vec2(1.0f, 1.0f);

	// Copy data into VBO:
	glGenBuffers(1, &m_texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), texCoord, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(2);
	delete[] texCoord;

	// Unbind the VAO
	glBindVertexArray(0);
}

void LIB_API Quad::render(glm::mat4 coords) {
}

void LIB_API Quad::render(unsigned int fboTexId) {
	// Render the mesh using VAO
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, fboTexId);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}