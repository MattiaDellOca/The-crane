#include "renderingList.h"


LIB_API RenderingList::RenderingList(std::string name) :
	Object(name), m_camera { nullptr } { };


std::list<RenderNode *> LIB_API RenderingList::getRenderingList() {
	return m_list;
}

void LIB_API RenderingList::setCamera(Camera *camera) {
	m_camera = camera;
}

void LIB_API RenderingList::pass(RenderNode *node) {
	if (dynamic_cast<const Light*>(node->m_node) != nullptr)
		m_list.push_front(node);
	else
		m_list.push_back(node);
}

void LIB_API RenderingList::clear() {
	m_list.clear();
}

void LIB_API RenderingList::render(glm::mat4) {
	// TODO calculte the matrix of each object
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		(*it)->m_node->render((*it)->m_mat);
		std::cout << glm::to_string((*it)->m_mat) << std::endl;
	}
}