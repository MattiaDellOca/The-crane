#pragma once

#include "lib.h"
#include "mesh.h"

class LIB_API Sphere : public Mesh {
private:
	float m_radius;
public:
	Sphere(float radius, std::string name, glm::mat4 matrix, Material *material);
	void render(glm::mat4);
};