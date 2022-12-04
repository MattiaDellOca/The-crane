#include "renderingList.h"

LIB_API RenderingList::RenderingList(std::string name) :
	Object(name), m_camera { nullptr } { };


std::list<Node>* LIB_API RenderingList::getRenderingList() {
	return m_list;
}

void LIB_API RenderingList::setCamera(Camera *camera) {
	m_camera = camera;
}

void LIB_API RenderingList::pass(Node node) {
	m_list->push_back(node);

	if (node.getNumberOfChildren() > 0) {
		for (auto* c : node.getChildren()) {
			m_list->push_back(*c);
		}
	}
}

void LIB_API RenderingList::sort() {
	for (auto it = m_list->begin(); it != m_list->end(); ++it) {
		if (dynamic_cast<const Light*>(it) != nullptr) {
			m_list->swap(it, m_list.front());
		}
	}
}

void LIB_API RenderingList::render() {
	for (auto it = m_list->begin(); it != m_list->end(); ++it) {
		it->render();
	}
}