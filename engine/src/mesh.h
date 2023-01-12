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


	/**
	 * \var m_cast_shadows
	 * \brief Indicates whether the mesh should cast shadows.
	 *
	 * m_cast_shadows is a member variable that holds a boolean value indicating whether the mesh should cast shadows. If set to true, the mesh will cast shadows when rendered in a scene. If set to false, the mesh will not cast shadows.
	 */
	bool m_cast_shadows;
public:
	/**
	 * \brief Constructor for the Mesh class.
	 *
	 * \param name The name of the mesh object.
	 * \param matrix The transformation matrix of the mesh object.
	 * \param material The material of the mesh. It is a pointer to a Material object.
	 * \param cast_shadows If true, the mesh will block light therefore creates a shadow.
	 */
	Mesh(const std::string& name, glm::mat4 matrix, Material* material = nullptr, bool cast_shadows = true);

	/**
	 * \brief Renders the mesh object.
	 *
	 * This function is called to render the mesh object in the scene. It is derived from the Node class and is overridden in the Mesh class to perform specific rendering tasks for meshes.
	 *
	 * \param coords The pre-computed world coordinates of the mesh object.
	 */
	void render(glm::mat4 coords) override;

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

	/**
	* \brief Enables or disables shadow casting for the mesh object.
	*
	* \param enabled Set to true to enable shadow casting for the mesh, or false to disable it.
	*/
	void setShadowCast(bool enabled);
	
	/**
	* \brief Returns whether shadow casting is enabled for the mesh object.
	*
	* \return True if shadow casting is enabled for the mesh, false if it is disabled.
	*/
	bool isShadowCastEnabled() const;
	
	/**
	* \brief Renders a shadow for the mesh object.
	*
	* This function is called to render a shadow for the mesh object in the scene. It is used to create the appearance of a shadow being cast by the mesh.
	*
	* \param cameraInv The inverse of the camera matrix.
	* \param parentRelativeCoords The parent-relative coordinates of the mesh object.
	*/
	void renderShadow(glm::mat4 cameraInv, glm::mat4 parentRelativeCoords);
};