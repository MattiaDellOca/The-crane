//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "object.h"

/////////////
// CLASSES //
/////////////

unsigned int Object::m_incemental_id = 0;

Object::Object(std::string name) :
	m_id{ m_incemental_id++ },
	m_name{ name } {};

// Object::~Object() {}

void Object::setName(std::string name) {
	m_name = name;
}

const std::string Object::getName() {
	return m_name;
}

const unsigned int Object::getId() {
	return m_id;
}