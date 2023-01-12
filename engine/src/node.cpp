//////////////
// #INCLUDE //
//////////////

// Library main include
#include "node.h"
#include <GL/freeglut.h>

/////////////
// CLASSES //
/////////////

LIB_API Node::Node(const std::string& name, glm::mat4 matrix) :
	Object(name), m_matrix{ matrix }, m_parent{ nullptr } {};


LIB_API Node::~Node() {
	//if the node has no children remove the pointer to the parent
	//else if delete them

		for (Node* node : m_children) {
			delete node;
		}
		m_children.clear();
}

const glm::mat4 LIB_API Node::getMatrix() {
	return m_matrix;
}

const std::vector<Node*> LIB_API Node::getChildren() {
	return m_children;
}

unsigned int LIB_API Node::getNumberOfChildren() {
	return static_cast<unsigned int>(m_children.size());
}

Node* Node::getChild(int pos) {
	return m_children.at(pos);
}

Node* Node::getParent() {
	return m_parent;
}

void LIB_API Node::setMatrix(glm::mat4 matrix) {
	m_matrix = matrix;
}

void LIB_API Node::setParent(Node* parent) {
	parent->addChild(this);
}

void LIB_API Node::addChild(Node* child) {
	// Set parent + recursive matrix
	//child->setParent(this);
	child->m_parent = this;

	// Check if children is nullptr
	m_children.push_back(child);
}

bool LIB_API Node::removeChild(Node* child) {
	for (int i = 0; static_cast<unsigned int>(i) < getNumberOfChildren(); i++) {
		if (child->m_id == getChild(i)->m_id) {
			m_children.erase(m_children.begin() + i);
			return true;
		}
	}

	return false;
}

void LIB_API Node::render(glm::mat4 matrix) {
	glLoadMatrixf(glm::value_ptr(matrix));
}


 Node LIB_API* Node::searchNode(const char* name) {

	 //if the names match returns
	if (name == m_name) {
		return this;
	}
	
	//search in each children
	for (Node* node : m_children) {

		//recurive call (BFS)
		Node* result = node->searchNode(name);

		//check for result
		if (result != nullptr) {
			return result;
		}
	}
	
	//if the node is not found return null
	return nullptr;
}


 const glm::mat4 LIB_API Node::getWorldCoordinateMatrix() {

		 glm::mat4 worldCoordinate(1.f);

		 Node* currentNode = this;
		 while (currentNode != nullptr) {
			 worldCoordinate = currentNode->m_matrix * worldCoordinate;
			 currentNode = currentNode->m_parent;
		 }

		 return worldCoordinate;
	 
 }