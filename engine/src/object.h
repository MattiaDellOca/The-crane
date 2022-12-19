#pragma once

//////////////
// #INCLUDE //
//////////////

	// Library main include
#include "lib.h"

	// C/C++
#include <string>

	//GLM
#include <glm/glm.hpp>


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
	virtual ~Object() = 0;

	void setName(std::string);
	const std::string getName();
	const unsigned int getId();
	// render with parameters
	void virtual render(glm::mat4) = 0;
};
