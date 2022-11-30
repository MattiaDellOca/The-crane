#pragma once

#include "lib.h"
#include "node.h"

class LIB_API Mesh : public Node {
public:
	Mesh(std::string name, glm::mat4 matrix);
	virtual void render() = 0;
};