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

void LIB_API RenderingList::sort() {
	m_list.sort(sortCondition);
}

void LIB_API RenderingList::clear() {
	m_list.clear();
}

void LIB_API RenderingList::render() {
	// TODO calculte the matrix of each object
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		(*it)->render();
	}
}