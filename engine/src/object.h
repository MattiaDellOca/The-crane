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

/**
 * \class Object
 * \brief Base class for objects in the scene.
 *
 * Object is the base class for objects in the scene. It has member variables and functions that are common to all objects. It has a name and a unique identifier.
 *
 * The Object class also has functions to set and get the name and identifier of the object, and a virtual function to render the object in the scene.
 */
class LIB_API Object {
protected:
	/**
	 * \var m_id
	 * \brief The unique identifier of the object.
	 *
	 * m_id is a member variable that holds the unique identifier of the object. It is an unsigned integer value.
	 */
	unsigned int m_id;

	/**
	 * \var m_name
	 * \brief The name of the object.
	 *
	 * m_name is a member variable that holds the name of the object. It is a string value.
	 */
	std::string m_name;

	/**
	 * \var m_incremental_id
	 * \brief The incremental identifier for objects.
	 *
	 * m_incremental_id is a static member variable that is used to assign unique identifiers to objects. It is an unsigned integer value.
	 */
	static unsigned int m_incemental_id;
public:

	/**
	 * \brief Constructor for the Object class.
	 *
	 * \param name The name of the object.
	 */
	Object(std::string name);

	/**
	 * \brief Destructor for the Object class.
	 */
	virtual ~Object() = 0;

	/**
	 * \brief Sets the name of the object.
	 *
	 * \param name The name to be set. It is a string value.
	 */
	void setName(std::string name);

	/**
	 * \brief Gets the name of the object.
	 *
	 * \return The name of the object. It is a string value.
	 */
	const std::string getName();
	
	/**
	 * \brief Gets the unique identifier of the object.
	 *
	 * \return The unique identifier of the object. It is an unsigned integer value.
	 */
	const unsigned int getId();
	
	/**
	 * \brief Renders the object.
	 *
	 * This is a virtual function that is called to render the object in the scene. It must be overridden in derived classes to perform specific rendering tasks for different types of objects.
	 *
	 * \param coords The pre-computed world coordinates of the object.
	 */
	void virtual render(glm::mat4 coords) = 0;
};
