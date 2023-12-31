//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "object.h"

/////////////
// CLASSES //
/////////////

unsigned int LIB_API Object::m_incremental_id = 0;

LIB_API Object::Object(const std::string& name) :
	m_id{ m_incremental_id++ },
	m_name{ name } {};

LIB_API Object::~Object() {}

void LIB_API Object::setName(const std::string& name) {
	m_name = name;
}

const LIB_API std::string Object::getName() {
	return m_name;
}

const LIB_API unsigned int Object::getId() {
	return m_id;
}