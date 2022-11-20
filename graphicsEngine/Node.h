//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "BaseEntity.h"

	// C/C++
#include <vector>
#include <string>

	// GLM:
#include <glm/glm.hpp>


class Node : public BaseEntity {
protected:
	glm::mat4 m_matrix;
	std::vector<Node*> m_children;
	Node* m_parent;

public:
	Node(std::string, glm::mat4);
	const glm::mat4 getMatrix() const;
	const std::vector<Node*> getChildren();
	int getNumberOfChildren();
	const Node* getChild(int);
	const Node* getParent();
	void setMatrix(glm::mat4);
	void setParent(Node*);
	void addChild(Node*);
	bool removeChild(Node*);
};