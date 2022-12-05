#include "renderingList.h"


bool LIB_API RenderingList::sortCondition(Object* o1, Object* o2) {
	return dynamic_cast<const Light*>(o1) != nullptr;
}

LIB_API RenderingList::RenderingList(std::string name) :
	Object(name), m_camera { nullptr } { };


std::list<Object *> LIB_API RenderingList::getRenderingList() {
	return m_list;
}

void LIB_API RenderingList::setCamera(Camera *camera) {
	m_camera = camera;
}

void LIB_API RenderingList::pass(Object* object) {
	m_list.push_back(object);
}

// 1. sorted set (operatore as)
// 2. priority queue (implementare operatore <)
void LIB_API RenderingList::sort() {
	// quick sort con condizione luce
	//std::sort(m_list.begin(), m_list.end(), sortCondition);
	m_list.sort(sortCondition);
}

void LIB_API RenderingList::clear() {
	m_list.clear();
}

void LIB_API RenderingList::render() {
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		(*it)->render();
	}
}