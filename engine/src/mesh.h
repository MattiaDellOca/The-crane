#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"

//GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>


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
	* \var m_vertex_vbo
	* \brief The VBO id for vertices.
	*
	* m_vertex_vbo is a member variable that holds the VBO id of the vertices of this mesh.
	*/
	unsigned int m_vertex_vbo;

	/**
	* \var m_normal_vbo
	* \brief The VBO id for normals.
	*
	* m_normal_vbo is a member variable that holds the VBO id of the normals of this mesh.
	*/
	unsigned int m_normal_vbo;

	/**
	* \var m_texture_vbo
	* \brief The VBO id for textures.
	*
	* m_texture_vbo is a member variable that holds the VBO id of the textures of this mesh.
	*/
	unsigned int m_texture_vbo;

	/**
	* \var m_face_index_vbo
	* \brief The VBO id for face indexes.
	*
	* m_face_index_vbo is a member variable that holds the VBO id of the face indexes of this mesh.
	*/
	unsigned int m_face_index_vbo;

	/**
	* \var m_vao
	* \brief The VAO id for thish mesh.
	*
	* m_face_index_vbo is a member variable that holds the VAO id of this mesh.
	*/
	unsigned int m_vao;

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
	 * \param faces The number of faces in the mesh.
	 * \param vertexVbo The vertex buffer object (VBO) containing the vertices of the mesh.
	 * \param normalVbo The VBO containing the normals of the mesh.
	 * \param textureVbo The VBO containing the texture coordinates of the mesh.
	 * \param faceIndexVbo The VBO containing the indices of the faces of the mesh.
	 * \param vao The vertex array object (VAO) of the mesh.
	 * \param material The material of the mesh. It is a pointer to a Material object.
	 * \param cast_shadows If true, the mesh will block light therefore creates a shadow.
	 */
	Mesh(const std::string& name, glm::mat4 matrix,unsigned int faces, unsigned int vertexVbo, unsigned int normalVbo, unsigned int textureVbo, unsigned int faceIndexVbo, unsigned int vao, Material* material = nullptr, bool cast_shadows = true);

	/**
	* \brief Destructor for the Mesh class.
	*/
	~Mesh();

	/**
	* \brief Copy constructor for the Mesh class.
	*
	* \param o The Mesh object to copy.
	*/
	Mesh(const Mesh& o) = delete;

	/**
	* \brief Copy assignment operator for the Mesh class.
	*
	* \param o The Mesh object to copy.
	* \returns A reference to the Mesh object.
	*/
	Mesh& operator=(const Mesh& o) = delete;

	/**
	* \brief Move constructor for the Mesh class.
	*
	* \param o The Mesh object to move.
	*/
	Mesh(Mesh&& o) = delete;

	/**
	* \brief move assignment operator for the Mesh class.
	*
	* \param o The Mesh object to move.
	* \returns A reference to the Mesh object.
	*/
	Mesh& operator=(Mesh&& o) = delete;

	/**
	 * \brief Renders the mesh object.
	 *
	 * This function is called to render the mesh object in the scene. It is derived from the Node class and is overridden in the Mesh class to perform specific rendering tasks for meshes.
	 *
	 * \param coords The pre-computed world coordinates of the mesh object.
	 */
	void render(glm::mat4 coords) override;

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