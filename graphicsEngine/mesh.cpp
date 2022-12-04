#include "mesh.h"

LIB_API Mesh::Mesh(std::string name, glm::mat4 matrix) : Node(name, matrix) {};

Material LIB_API Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material material) {
	m_material = material;
}