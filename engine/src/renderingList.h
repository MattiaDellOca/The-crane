#pragma once

#include "lib.h"
#include "object.h"
#include "mesh.h"
#include "light.h"
#include "camera.h"

#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

/**
 * \struct RenderNode
 * \brief A structure that holds a node and its transformation matrix.
 *
 * RenderNode is a structure that holds a node and its transformation matrix. It is used to store nodes that need to be rendered in the scene.
 *
 * The RenderNode structure has two member variables:
 *  - m_node: a pointer to an Object object. It represents the node to be rendered.
 *  - m_mat: a 4x4 matrix that represents the transformation of the node. (World Coordinates)
 */
struct RenderNode {
	Object* m_node;
	glm::mat4 m_mat;
};

/**
 * \class RenderingList
 * \brief A class for storing and rendering a list of nodes.
 *
 * RenderingList is a class for storing and rendering a list of nodes in the scene. It is derived from the Object class and has member variables and functions for managing the list of nodes.
 *
 * The RenderingList class has a member variable called m_list, which is a list of pointers to RenderNode structures. It also has member functions to add nodes to the list, get the list, clear the list, and render the nodes in the list.
 */
class LIB_API RenderingList : public Object {
protected:
	/**
	 * \var m_list
	 * \brief The list of nodes to be rendered.
	 *
	 * m_list is a member variable that holds the list of nodes to be rendered. It is a list of pointers to RenderNode structures.
	 */
	std::list<RenderNode *> m_list;

	/**
	 * \brief Load a RenderNode in the rendering list, putting Lights first.
	 *
	 * \param node The node to be rendered.
	 */
	void loadRenderNode(RenderNode* node);
public:
	/**
	 * \brief Constructor for the RenderingList class.
	 *
	 * \param name The name of the rendering list.
	 */
	explicit RenderingList(const std::string& name);



	/**
	* \brief Destructor for the RenderingList class.
	*/
	~RenderingList();

	/**
	* \brief Copy constructor for the RenderingList class.
	*
	* \param o The RenderingList object to copy.
	*/
	RenderingList(const RenderingList& o) = delete;

	/**
	* \brief Copy assignment operator for the RenderingList class.
	*
	* \param o The RenderingList object to copy.
	* \returns A reference to the RenderingList object.
	*/
	RenderingList& operator=(const RenderingList& o) = delete;

	/**
	* \brief Move constructor for the RenderingList class.
	*
	* \param o The RenderingList object to move.
	*/
	RenderingList(RenderingList&& o) = delete;

	/**
	* \brief move assignment operator for the RenderingList class.
	*
	* \param o The RenderingList object to move.
	* \returns A reference to the RenderingList object.
	*/
	RenderingList& operator=(RenderingList&& o) = delete;


	/**
	 * \brief Gets the list of nodes to be rendered.
	 *
	 * \return The list of nodes to be rendered. It is a list of pointers to RenderNode structures.
	 */
	std::list<RenderNode*> getRenderingList();

	/**
	 * \brief Adds nodes and their transformation matrices to the list.
	 *
	 * This function is used to recursively add nodes and their transformation matrices to the rendering list. 
	 * It traverses the hierarchy of nodes and adds each node and its transformation matrix to the list.
	 *
	 * \param node The root node of the hierarchy to be added to the list.
	 * \param parentMatrix The transformation matrix of the root node.
	 */
	void pass(Node* node, glm::mat4 parentMatrix);

	/**
	 * \brief Clears the list of nodes.
	 *
	 * This function clears the list of nodes and frees the memory allocated to the nodes.
	 */
	void clear();

	/**
	 * \brief Renders the nodes in the list.
	 *
	 * This function iterates through the list of nodes and calls the render function of each node, passing the pre-computed world coordinates of the node.
	 *
	 * \param cameraMatrix The camera matrix of the scene. It is a 4x4 matrix that represents the position and orientation of the camera in the scene.
	 */
	void render(glm::mat4 cameraMatrix) override;
};
