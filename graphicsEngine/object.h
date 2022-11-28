#pragma once

//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "lib.h"

	// C/C++
#include <string>

/////////////
// CLASSES //
/////////////

class LIB_API Object {
protected:
	unsigned int m_id;
	std::string m_name;
	static unsigned int m_incemental_id;
public:
	Object(std::string);
	// virtual ~Object() = 0;

	void setName(std::string);
	const std::string getName();
	const unsigned int getId();
	void virtual render() = 0;
};
