#pragma once

#include "lib.h"
#include "object.h"

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
	 * m_ambient is a member variable that holds the ambient color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_ambient = glm::vec4{ 0.2f, 0.2f, 0.2f, 1.0f };
	
	/**
	 * \var m_diffuse
	 * \brief The diffuse color of the material.
	 *
	 * m_diffuse is a member variable that holds the diffuse color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_diffuse = glm::vec4{ 0.8f, 0.8f, 0.8f, 1.0f };
	
	/**
	 * \var m_specular
	 * \brief The specular color of the material.
	 *
	 * m_specular is a member variable that holds the specular color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_specular = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
	
	/**
	 * \var m_emission
	 * \brief The emission color of the material.
	 *
	 * m_emission is a member variable that holds the emission color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_emission = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

	/**
	 * \var m_shininess
	 * \brief The shininess value of the material.
	 *
	 * m_shininess is a member variable that holds the shininess value of the material. It is a float value that determines the specular highlight size and intensity.
	 */
	float m_shininess = 0.0f;
public:
	/**
	 * \brief Constructor for the Material class.
	 *
	 * \param name The name of the material.
	 */
	Material(std::string name);

	/**
	 * \brief Applies the material.
	 *
	 * This function sets the values of the material's member variables in opengl settings, so that they can be used to render the objects in the scene.
	 */
	void apply();
	
	void setAmbient(glm::vec4 ambient);

	/**
	 * \brief Sets the diffuse color of the material.
	 *
	 * \param diffuse The diffuse color to be set. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	void setDiffuse(glm::vec4 diffuse);

	/**
	 * \brief Sets the specular color of the material.
	 *
	 * \param specular The specular color to be set. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	void setSpecular(glm::vec4 specular);
	
	/**
	 * \brief Sets the shininess value of the material.
	 *
	 * \param shininess The shininess value to be set. It is a float value that determines the specular highlight size and intensity.
	 */
	void setShininess(float shininess);

	/**
	 * \brief Sets the emission color of the material.
	 *
	 * \param emission The emission color to be set. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	void setEmission(glm::vec4 emission);

	/**
	 * \brief Gets the ambient color of the material.
	 *
	 * \return The ambient color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 getAmbient() const;

	/**
	 * \brief Gets the diffuse color of the material.
	 *
	 * \return The diffuse color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 getDiffuse() const;

	/**
	 * \brief Gets the specular color of the material.
	 *
	 * \return The specular color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 getSpecular() const;

	/**
	 * \brief Gets the emission color of the material.
	 *
	 * \return The emission color of the material. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 getEmission() const;

	/**
	 * \brief Gets the shininess value of the material.
	 *
	 * \return The shininess value of the material. It is a float value that determines the specular highlight size and intensity.
	 */
	float getShininess() const;

	// Inherited via Object
	virtual void render(glm::mat4 coords) override;
};