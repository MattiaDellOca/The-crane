#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"

//GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LIB_API Mesh : public Node {
protected:
	Material m_material;
public:
	Mesh(std::string name, glm::mat4 matrix, Material material);
	void render(glm::mat4);
	const Material& getMaterial();
	void setMaterial(Material);
};