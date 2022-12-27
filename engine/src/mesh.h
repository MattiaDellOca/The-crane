#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"
#include "vertex.h"

//GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

/**
 * \class Mesh
 * \brief Class representing a mesh object in the scene.
 *
 * Mesh is a class that represents a mesh object in the scene. It is derived from the Node class and has additional member variables and functions specific to mesh objects. It has a vector of vertices and a material.
 *
 * The Mesh class also has functions to set and get the material of the mesh, add vertices to the mesh, and render the mesh in the scene.
 */
class LIB_API Mesh : public Node {
protected:
	/**
	 * \var m_vertices
	 * \brief The vertices of the mesh.
	 *
	 * m_vertices is a member variable that holds the vertices of the mesh. It is a vector of pointers to Vertex objects.
	 */
	std::vector<Vertex*> m_vertices;
	
	/**
	 * \var m_material
	 * \brief The material of the mesh.
	 *
	 * m_material is a member variable that holds the material of the mesh. It is a pointer to a Material object.
	 */
	Material *m_material;

	/**
	* \var m_faces
	* \brief The number of faces of the mesh.
	* 
	* m_faces is a member variable that holds the number of faces of this mesh.
	*/
	unsigned int m_faces;
public:
	/**
	 * \brief Constructor for the Mesh class.
	 *
	 * \param name The name of the mesh object.
	 * \param matrix The transformation matrix of the mesh object.
	 * \param material The material of the mesh. It is a pointer to a Material object.
	 */
	Mesh(std::string name, glm::mat4 matrix, Material* material = nullptr);

	/**
	 * \brief Renders the mesh object.
	 *
	 * This function is called to render the mesh object in the scene. It is derived from the Node class and is overridden in the Mesh class to perform specific rendering tasks for meshes.
	 *
	 * \param coords The pre-computed world coordinates of the mesh object.
	 */
	void render(glm::mat4 coords);

	/**
	 * \brief Gets the material of the mesh.
	 *
	 * \return The material of the mesh. It is a pointer to a Material object.
	 */
	const Material* getMaterial();


	/**
	 * \brief Sets the material of the mesh.
	 *
	 * \param material The material to be set. It is a pointer to a Material object.
	 */
	void setMaterial(Material* material);

	/**
	 * \brief Adds a vertex to the mesh.
	 *
	 * \param vertex The vertex to be added. It is a pointer to a Vertex object.
	 */
	void addVertex(Vertex* vertex);

	/**
	* \brief Adds a new face (a triangle) to the list of faces.
	* 
	* \param v1 Pointer to the first Vertex object.
	* \param v2 Pointer to the second Vertex object.
	* \param v3 Pointer to the third Vertex object.
	*/
	void addFace(Vertex* v1, Vertex* v2, Vertex* v3);
};