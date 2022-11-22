//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "baseentity.h"

/////////////
// CLASSES //
/////////////

unsigned int BaseEntity::m_incemental_id = 0;

BaseEntity::BaseEntity(std::string name) :
	m_id{ m_incemental_id++ },
	m_name{ name } {};

void BaseEntity::setName(std::string name) {
	m_name = name;
}

const std::string BaseEntity::getName() {
	return m_name;
}

const unsigned int BaseEntity::getId() {
	return m_id;
}