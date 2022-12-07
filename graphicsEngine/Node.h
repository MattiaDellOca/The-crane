#pragma once

//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "object.h"

	// C/C++
#include <vector>
#include <string>
#include <iostream>

	// GLM
#include <glm/glm.hpp>

class LIB_API Node : public Object {
protected:
	glm::mat4 m_matrix;
	std::vector<Node*> * m_children; // https://stackoverflow.com/a/6869033
	Node* m_parent;
public:
	Node(std::string, glm::mat4);
	virtual ~Node();

	const glm::mat4 getMatrix() const;
	const std::vector<Node*> getChildren();
	int getNumberOfChildren();
	Node* getChild(int);
	const Node* getParent();
	void setMatrix(glm::mat4);
	void setParent(Node*);
	void addChild(Node*);
	bool removeChild(Node*);
	void virtual render(glm::mat4);
};