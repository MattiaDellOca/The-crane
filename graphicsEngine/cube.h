#pragma once

#include "lib.h"
#include "mesh.h"

class LIB_API Cube : public Mesh {
private:
	float m_edge;
public:
	Cube(float edge, std::string name, glm::mat4 matrix);
	void render();
};