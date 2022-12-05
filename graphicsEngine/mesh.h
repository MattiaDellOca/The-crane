#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"

class LIB_API Mesh : public Node {
protected:
	Material m_material;
public:
	Mesh(std::string name, glm::mat4 matrix, Material material);
	void render();
	const Material& getMaterial();
	void setMaterial(Material);
};