
#include "sphere.h"

Sphere::Sphere(int radius, glm::mat4 matrix, std::string name) : Node(&name, &matrix), m_radius{ radius } {};

void Sphere::render() {
	std::cout << "HELLO" << std::endl;
}