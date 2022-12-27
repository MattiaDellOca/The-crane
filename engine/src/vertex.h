#pragma once

#include "lib.h"
#include <glm/glm.hpp>

/**
 * \class Vertex
 * \brief A class for representing a vertex in 3D space.
 *
 * Vertex is a class for representing a vertex in 3D space. It has member variables for the position, normal, texture coordinates, and tangent of the vertex.
 *
 * The Vertex class has member functions to get the values of these member variables, as well as a constructor that initializes the member variables with the provided values.
 */
class LIB_API Vertex {
private:
	/**
	 * \var m_position
	 * \brief The position of the vertex in 3D space.
	 *
	 * m_position is a member variable that holds the position of the vertex in 3D space. It is a 3D vector represented by a glm::vec3 object.
	 */
	glm::vec3 m_position;

	/**
	 * \var m_normal
	 * \brief The normal of the vertex.
	 *
	 * m_normal is a member variable that holds the normal of the vertex. It is a 3D vector represented by a glm::vec4 object.
	 */
	glm::vec4 m_normal;

	/**
	 * \var m_texture
	 * \brief The texture coordinates of the vertex.
	 *
	 * m_texture is a member variable that holds the texture coordinates of the vertex. It is a 2D vector represented by a glm::vec2 object.
	 */
	glm::vec2 m_texture;

	/**
	 * \var m_tangent
	 * \brief The tangent of the vertex.
	 *
	 * m_tangent is a member variable that holds the tangent of the vertex. It is a 3D vector represented by a glm::vec4 object.
	 */
	glm::vec4 m_tangent;

public:
	/**
	 * \brief Constructor for the Vertex class.
	 *
	 * This is the constructor for the Vertex class. It initializes the member variables with the provided values.
	 *
	 * \param position The position of the vertex in 3D space. It is a 3D vector represented by a glm::vec3 object.
	 * \param normal The normal of the vertex. It is a 3D vector represented by a glm::vec4 object. The fourth component of the vector is used to store the handedness of the normal.
	 * \param texture The texture coordinates of the vertex. It is a 2D vector represented by a glm::vec2 object.
	 * \param tangent The tangent of the vertex. It is a 3D vector represented by a glm::vec4 object. The fourth component of the vector is used to store the handedness of the tangent.
	 */
	Vertex(glm::vec3& position, glm::vec4& normal, glm::vec2& texture, glm::vec4& tangent);
	
	/**
	 * \brief Gets the position of the vertex.
	 *
	 * \return The position of the vertex. It is a 3D vector represented by a glm::vec3 object.
	 */
	const glm::vec3 getPosition();


	/**
	 * \brief Gets the normal of the vertex.
	 *
	 * \return The normal of the vertex. It is a 3D vector represented by a glm::vec4 object. The fourth component of the vector is used to store the handedness of the normal.
	 */
	const glm::vec4 getNormal();

	/**
	 * \brief Gets the texture coordinates of the vertex.
	 *
	 * \return The texture coordinates of the vertex. It is a 2D vector represented by a glm::vec2 object.
	 */
	const glm::vec2 getTexture();

	/**
	 * \brief Gets the tangent of the vertex.
	 *
	 * \return The tangent of the vertex. It is a 3D vector represented by a glm::vec4 object. The fourth component of the vector is used to store the handedness of the tangent.
	 */
	const glm::vec4 getTangent();
};