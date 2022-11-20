//////////////
// #INCLUDE //
//////////////

	// C/C++
#include <string>


/////////////
// CLASSES //
/////////////

class BaseEntity {
protected:
	unsigned int m_id;
	std::string m_name;
	static unsigned int m_incemental_id;

public:
	BaseEntity(std::string) {};
	// Destructor?

	void setName(std::string);
	const std::string getName();
	const unsigned int getId();
	void virtual render();
};