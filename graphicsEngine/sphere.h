#pragma once

#include "lib.h"
#include "node.h"

class LIB_API Sphere : public Node {
private:
	int m_radius;

public:
	Sphere(int radius, glm::mat4 matrix, std::string name);
	void render();
};