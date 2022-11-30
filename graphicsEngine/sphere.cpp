
#include "sphere.h"

LIB_API Sphere::Sphere(int radius, glm::mat4 matrix, std::string name) : Node(name, matrix), m_radius{ radius } {};

void LIB_API Sphere::render() {
	std::cout << "HELLO" << std::endl;
}