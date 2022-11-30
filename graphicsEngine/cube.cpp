#include "cube.h"

LIB_API Cube::Cube(float edge, std::string name, glm::mat4 matrix) : Mesh{ name,matrix }, m_edge{edge} {};

void LIB_API Cube::render() {
	std::cout << "CUBE: edge: " << m_edge << " Name: " << m_name << std::endl;
}