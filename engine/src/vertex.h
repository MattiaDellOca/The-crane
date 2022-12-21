#pragma once

#include "lib.h"
#include <glm/glm.hpp>

class LIB_API Vertex {
private:
	glm::vec3 m_position;
	glm::vec4 m_normal;
	glm::vec2 m_texture;
	glm::vec4 m_tangent;

public:
	Vertex(glm::vec3 m_position, glm::vec4 m_normal, glm::vec2 m_texture, glm::vec4 m_tangent);
	const glm::vec3 getPosition();
	const glm::vec4 getNormal();
	const glm::vec2 getTexture();
	const glm::vec4 getTangent();
};