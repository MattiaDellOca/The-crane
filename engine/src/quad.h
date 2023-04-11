#pragma once

// Project classes
#include "object.h"
#include "shaderWrapper.h"

// GLM:
#include <glm/glm.hpp>

class LIB_API Quad : public Object {
private:
	unsigned int m_vertex_vbo = 0;
	unsigned int m_texture_vbo = 0;
	unsigned int m_vao = 0;

	unsigned int m_window_size_x;
	unsigned int m_window_size_y;

	void createPlane();
public:
	Quad(const std::string&, unsigned int, unsigned int);

	~Quad();

	/**
	* \brief Renders the node and its children.
	* \param coords The pre-computed world coordinates of the node.
	*/
	virtual void render(glm::mat4) override;

	void render(unsigned int);
};