#include "renderingList.h"


LIB_API RenderingList::RenderingList(std::string name) :
	Object(name) { };

void RenderingList::loadRenderNode(RenderNode* node) {
	if (dynamic_cast<const Light*>(node->m_node) != nullptr)
		m_list.push_front(node);
	else
		m_list.push_back(node);
}

std::list<RenderNode *> LIB_API RenderingList::getRenderingList() {
	return m_list;
}


void LIB_API RenderingList::pass(Node *node, glm::mat4 parentMatrix) {
	if (node == NULL)
		return;

	// Matrix expressed in world coordinates
	glm::mat4 wcMatrix = parentMatrix * node->getMatrix();


	// If concrete type of node is either Mesh or Light (therefore NOT Camera), load it in the rendering list,
	// otherwise skip the operation!
	if (dynamic_cast<const Camera*>(node) == nullptr && 
		dynamic_cast<const Light*>(node) != nullptr || dynamic_cast<const Node*>(node) != nullptr) {
		loadRenderNode(new RenderNode{ node, wcMatrix });
	}

	if (node->getNumberOfChildren() > 0) {
		for (auto* child : node->getChildren()) {
			pass(child, wcMatrix);
		}
	}
}

void LIB_API RenderingList::clear() {
	m_list.clear();
}

void LIB_API RenderingList::render(glm::mat4 cameraMatrix) {
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		// call render method for each node
		(*it)->m_node->render(glm::inverse(cameraMatrix) * (*it)->m_mat);
	}
}