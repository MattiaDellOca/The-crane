#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"
#include "vertex.h"

//GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class LIB_API Mesh : public Node {
protected:
	std::vector<Vertex*> m_vertices;
	Material *m_material;
public:
	Mesh(std::string name, glm::mat4 matrix, Material *material);
	void render(glm::mat4);
	const Material *getMaterial();
	void setMaterial(Material*);
	void addVertex(Vertex* vertex);
};