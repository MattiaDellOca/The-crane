#include "mesh.h"

LIB_API Mesh::Mesh(std::string name, glm::mat4 matrix, Material material) : Node(name, matrix), m_material{ material } {};

const Material LIB_API& Mesh::getMaterial() {
	return m_material;
}

void LIB_API Mesh::setMaterial(Material material) {
	m_material = material;
}

void LIB_API Mesh::render() {
	std::cout << "MESH: name: " << m_name << "id: " << m_id << std::endl;
}