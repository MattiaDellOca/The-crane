#pragma once

//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "object.h"

	// C/C++
#include <vector>
#include <string>
#include <iostream>

	// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
 * \class Node
 * \brief Class representing a node in the scene.
 *
 * Node is a class that represents a node in the scene. It is derived from the Object class and has additional member variables and functions specific to nodes. It has a transformation matrix, a vector of child nodes, and a parent node.
 *
 * The Node class also has functions to set and get the transformation matrix, parent, and children of the node, add and remove children from the node, and render the node in the scene.
 */
class LIB_API Node : public Object {
protected:

	/**
	 * \var m_matrix
	 * \brief The transformation matrix of the node.
	 *
	 * m_matrix is a member variable that holds the transformation matrix of the node. It is a 4x4 matrix that represents the translation, rotation, and scale of the node in the scene.
	 */
	glm::mat4 m_matrix;

	/**
	 * \var m_children
	 * \brief The children of the node.
	 *
	 * m_children is a member variable that holds the children of the node. It is a vector of pointers to Node objects.
	 */
	std::vector<Node*> m_children;
	
	/**
	 * \var m_parent
	 * \brief The parent of the node.
	 *
	 * m_parent is a member variable that holds the parent of the node. It is a pointer to a Node object.
	 */
	Node* m_parent;
public:

	/**
	 * \brief Constructor for the Node class.
	 *
	 * \param name The name of the node.
	 * \param matrix The transformation matrix of the node.
	 */
	Node(std::string name, glm::mat4 matrix);

	/**
	 * \brief Destructor for the Node class.
	 */
	virtual ~Node();

	/**
	* \brief Copy constructor for the Node class.
	*
	* \param o The Node object to copy.
	*/
	Node(const Node& o) = delete;

	/**
	* \brief Copy assignment operator for the Node class.
	*
	* \param o The Node object to copy.
	* \returns A reference to the Node object.
	*/
	Node& operator=(const Node& o) = delete;

	/**
	 * \brief Gets the transformation matrix of the node.
	 *
	 * \return The transformation matrix of the node. It is a 4x4 matrix that represents the translation, rotation, and scale of the node in the scene.
	 */
	const glm::mat4 getMatrix();


	const glm::mat4 getWorldCoordinateMatrix();

	/**
	 * \brief Gets the children of the node.
	 *
	 * \return The children of the node. It is a vector of pointers to Node objects.
	 */
	const std::vector<Node*> getChildren();

	/**
	 * \brief Gets the number of children of the node.
	 *
	 * \return The number of children of the node. It is an integer value.
	 */
	unsigned int getNumberOfChildren();

	/**
	 * \brief Gets a child of the node.
	 *
	 * \param index The index of the child to be retrieved. It is an integer value.
	 *
	 * \return The child of the node at the given index. It is a pointer to a Node object.
	 */
	Node* getChild(int index);

	/**
	 * \brief Gets the parent of the node.
	 *
	 * \return The parent of the node. It is a pointer to a Node object.
	 */
	Node* getParent();

	/**
	 * \brief Sets the transformation matrix of the node.
	 *
	 * \param matrix The transformation matrix to be set. It is a 4x4 matrix that represents the translation, rotation, and scale of the node in the scene.
	 */
	void setMatrix(glm::mat4 matrix);

	/**
	 * \brief Sets the parent of the node.
	 *
	 * \param parent The parent to be set. It is a pointer to a Node object.
	 */
	void setParent(Node* parent);

	/**
	 * \brief Adds a child to the node.
	 *
	 * \param child The child to be added. It is a pointer to a Node object.
	 */
	void addChild(Node* child);
	
	/**
	 * \brief Removes a child from the node.
	 *
	 * \param child The child to be removed. It is a pointer to a Node object.
	 *
	 * \return A boolean value indicating whether the child was successfully removed or not.
	 */
	bool removeChild(Node* child);

	/**
	 * \brief Renders the node and its children.
	 *
	 * This function is called to render the node and its children in the scene. It is derived from the Object class and is overridden in the Node class to perform specific rendering tasks for nodes.
	 *
	 * \param coords The pre-computed world coordinates of the node.
	 */
	void virtual render(glm::mat4 coords) override;

	/**
	 * \brief Search a node based on his name
	 *
	 * This function is recursive and search on all child
	 *
	 * \param name of the node to be found
	 */
	Node* searchNode(const char* name);
};