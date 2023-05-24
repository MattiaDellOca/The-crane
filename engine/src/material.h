#pragma once

#include "lib.h"
#include "object.h"
#include "texture2D.h"

#include <iostream>

// GLM
#include <glm/glm.hpp>

/**
 * \class Material
 * \brief Class representing a material object in the scene.
 *
 * Material is a class that represents a material object in the scene. It is derived from the Object class and has additional member variables and functions specific to material objects. It has ambient, diffuse, specular, and emission color values, as well as a shininess value.
 *
 * The Material class also has functions to set and get the values of its member variables, and a function to apply the material to the rendering pipeline.
 */
class LIB_API Material : public Object {
private:
	/**
	 * \var m_ambient
	 * \brief The ambient color of the material.
	 *
	 * m_ambient is a member variable that holds the ambient color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 m_ambient;
	
	/**
	 * \var m_diffuse
	 * \brief The diffuse color of the material.
	 *
	 * m_diffuse is a member variable that holds the diffuse color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 m_diffuse;
	
	/**
	 * \var m_specular
	 * \brief The specular color of the material.
	 *
	 * m_specular is a member variable that holds the specular color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 m_specular;
	
	/**
	 * \var m_emission
	 * \brief The emission color of the material.
	 *
	 * m_emission is a member variable that holds the emission color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 m_emission;

	/**
	 * \var m_shininess
	 * \brief The shininess value of the material.
	 *
	 * m_shininess is a member variable that holds the shininess value of the material. It is a float value that determines the specular highlight size and intensity.
	 */
	float m_shininess;

	Texture* m_texture;
public:
	/**
	 * \brief Constructor for the Material class.
	 *
	 * \param name The name of the material.
	 */
	explicit Material(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, float shininess = 0.0f);

	/**
	* \brief Destructor for the Material class.
	*/
	~Material();

	/**
	* \brief Copy constructor for the Material class.
	*
	* \param o The Material object to copy.
	*/
	Material(const Material& o) = delete;

	/**
	* \brief Copy assignment operator for the Material class.
	*
	* \param o The Material object to copy.
	* \returns A reference to the Material object.
	*/
	Material& operator=(const Material& o) = delete;

	/**
	* \brief Move constructor for the Material class.
	*
	* \param o The Material object to move.
	*/
	Material(Material&& o) = delete;

	/**
	* \brief move assignment operator for the Material class.
	*
	* \param o The Material object to move.
	* \returns A reference to the Material object.
	*/
	Material& operator=(Material&& o) = delete;

	
	/**
	 * \brief Applies the material.
	 *
	 * This function sets the values of the material's member variables in opengl settings, so that they can be used to render the objects in the scene.
	 */
	void apply();

	/**
	 * \brief Gets the ambient color of the material.
	 *
	 * \return The ambient color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 getAmbient() const;

	/**
	 * \brief Gets the diffuse color of the material.
	 *
	 * \return The diffuse color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 getDiffuse() const;

	/**
	 * \brief Gets the specular color of the material.
	 *
	 * \return The specular color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 getSpecular() const;

	/**
	 * \brief Gets the emission color of the material.
	 *
	 * \return The emission color of the material. It is a 3D vector with the red, greena and blue channel values.
	 */
	glm::vec3 getEmission() const;

	/**
	 * \brief Gets the shininess value of the material.
	 *
	 * \return The shininess value of the material. It is a float value that determines the specular highlight size and intensity.
	 */
	float getShininess() const;

	/**
	 * \brief Gets the texture of the material.
	 *
	 * \returns The texture of the material.
	 */
	Texture* getTexture() const;
	
	/**
	 * \brief Sets the texture of the material.
	 *
	 * \param texture The texture to be set.
	 */
	void setTexture(Texture* texture);

	/**
	 * \brief Renders the material.
	 *
	 * \param coords Pre-computed world coordinates
	 */
	virtual void render(glm::mat4 coords) override;
};