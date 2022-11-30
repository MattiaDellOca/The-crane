//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "node.h"

/////////////
// CLASSES //
/////////////

Node::Node(std::string * name, glm::mat4 * matrix) :
	Object(name), m_matrix{ matrix }, m_parent{ nullptr }, m_children{ nullptr } {  };

/*
Node::~Node() {
	// Delete all allocated vars
	delete& m_matrix;

	// Empty each vector item + clear
	for (Node* node : m_children) {
		delete node;
	}
	m_children.clear();
	delete& m_children;

	// Delete parent node
	delete m_parent;
}
*/

const glm::mat4 LIB_API Node::getMatrix() const {
	return *m_matrix;
}

const std::vector<Node*> LIB_API Node::getChildren() {
	return *m_children;
}

int LIB_API Node::getNumberOfChildren() {
	return static_cast<int>(m_children->size());
}

const Node* Node::getChild(int pos) {
	return m_children->at(pos);
}

const Node* Node::getParent() {
	return m_parent;
}

void LIB_API Node::setMatrix(glm::mat4* matrix) {
	m_matrix = matrix;
}

void LIB_API Node::setParent(Node* parent) {
	m_parent = parent;
}

void LIB_API Node::addChild(Node* child) {
	m_children->push_back(child);
}

bool LIB_API Node::removeChild(Node* child) {
	for (int i = 0; i < getNumberOfChildren(); i++) {
		if (child->m_id == getChild(i)->m_id) {
			m_children->erase(m_children->begin() + i);
			return true;
		}
	}

	return false;
}

void LIB_API Node::render() {
	//TODO
}
