#pragma once

#include "node.h"
#include "lightType.h"

/**
 * \class Light
 * \brief Abstract class representing a light object in the scene.
 *
 * Light is an abstract class that represents a light object in the scene. It is derived from the Node class and has additional member variables and functions specific to light objects. It has a light type, an ID, and color values for ambient, diffuse, and specular lighting.
 *
 * \note This class is meant to be subclassed and should not be instantiated directly.
 */
class LIB_API Light : public Node {
protected:
	/**
	 * \var m_baseValueLights
	 * \brief The base value for the light ID.
	 *
	 * m_baseValueLights is a static variable that holds the base value for the light ID. It is used to generate unique IDs for each light object.
	 */
	static unsigned int m_baseValueLights;

	/**
	 * \var m_incrementalLightId
	 * \brief The incremental value for the light ID.
	 *
	 * m_incrementalLightId is a static variable that holds the incremental value for the light ID. It is used to generate unique IDs for each light object by adding it to the base value.
	 */
	static unsigned int m_incrementalLightId;

	/**
	 * \var m_maxLights
	 * \brief The maximum number of lights that OpenGL can manage.
	 *
	 * m_maxLights is a static variable that holds the maximum number of lights that OpenGL can manage. It is used to ensure that the number of lights in the scene does not exceed this limit.
	 */
	static int m_maxLights; //max lights that opengl can manage 

	/**
	 * \var m_type
	 * \brief The type of light.
	 *
	 * m_type is a member variable that holds the type of light. It can be one of the following values:
	 * - POINT_LIGHT
	 * - DIRECTIONAL_LIGHT
	 * - SPOT_LIGHT
	 */
	LightType m_type;

	/**
	 * \var m_lightId
	 * \brief The ID of the light.
	 *
	 * m_lightId is a member variable that holds the ID of the light. It is a unique identifier for the light object and is used to identify it in the scene.
	 */
	unsigned int m_lightId;

	/**
	 * \var m_lightAmbient
	 * \brief The ambient color of the light.
	 *
	 * m_lightAmbient is a member variable that holds the ambient color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_lightAmbient;

	/**
	 * \var m_lightDiffuse
	 * \brief The diffuse color of the light.
	 *
	 * m_lightDiffuse is a member variable that holds the diffuse color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_lightDiffuse;

	/**
	 * \var m_lightSpecular
	 * \brief The specular color of the light.
	 *
	 * m_lightSpecular is a member variable that holds the specular color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	glm::vec4 m_lightSpecular;

	/**
	 * \brief Constructor for the Light class.
	 *
	 * \param name The name of the light object.
	 * \param transform The transformation matrix for the light object.
	 * \param type The type of light. It can be one of the following values:
	 * - POINT_LIGHT
	 * - DIRECTIONAL_LIGHT
	 * - SPOT_LIGHT
	 * \param ambient The ambient color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 * \param diffuse The diffuse color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 * \param specular The specular color of the light. It is a 4D vector with the red, green, blue, and alpha channel values.
	 */
	Light(std::string name, glm::mat4 transform, LightType type, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);
public:
	/**
	 * \brief Renders the light object.
	 *
	 * This is a pure virtual function that must be implemented in the derived classes. It is called to render the light object in the scene.
	 *
	 * \param viewMatrix The view matrix for the scene.
	 */
	void virtual render(glm::mat4 viewMatrix) = 0;
	
	/**
	* \brief Gets the ID of the light.
	*
	* \returns The ID of the light.
	*/
	const unsigned int& getLightId();

	/**
	* \brief Gets the type of the light.
	*
	* \returns The type of the light (DIRECTIONAL, OMNIDIRECTIONAL, or SPOT).
	*/
	const LightType& getLightType();
};