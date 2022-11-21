//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "Node.h"


/////////////
// CLASSES //
/////////////

Node::Node(std::string name, glm::mat4 matrix) : 
	BaseEntity(name), m_matrix{ matrix } {  };

const glm::mat4 Node::getMatrix() const {
	return m_matrix;
}

const std::vector<Node*> Node::getChildren() {
	return m_children;
}

int Node::getNumberOfChildren() {
	return static_cast<int>(m_children.size());
}

const Node* Node::getChild(int pos) {
	return m_children.at(pos);
}

const Node* Node::getParent() {
	return m_parent;
}

void Node::setMatrix(glm::mat4 matrix) {
	m_matrix = matrix;
}

void Node::setParent(Node* parent) {
	m_parent = parent;
}

void Node::addChild(Node* child) {
	m_children.push_back(child);
}

bool Node::removeChild(Node* child) {
	for (int i = 0; i < getNumberOfChildren(); i++) {
		if (child->m_id == getChild(i)->m_id) {
			m_children.erase(m_children.begin() + i);
			return true;
		}
	}

	return false;
}

void Node::render() {
	//TODO
}
