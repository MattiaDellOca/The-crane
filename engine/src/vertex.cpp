#include "vertex.h"

LIB_API Vertex::Vertex(glm::vec3& position, glm::vec4& normal, glm::vec2& texture, glm::vec4& tangent) :
	m_position{ position }, m_normal{ normal }, m_texture{ texture }, m_tangent{ tangent } {};

const glm::vec3 LIB_API Vertex::getPosition() {
	return m_position;
}

const glm::vec4 LIB_API Vertex::getNormal() {
	return m_normal;
}

const glm::vec2 LIB_API Vertex::getTexture() {
	return m_texture;
}

const glm::vec4 LIB_API Vertex::getTangent() {
	return m_tangent;
}