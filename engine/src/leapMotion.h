#pragma once

 //////////////
 // #INCLUDE //
 //////////////

	// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>   

// C/C++:
#include <iostream>
#include<vector>

// Leap Motion SDK:
#include <LeapC.h>

// Project classes
#include "node.h"
#include "shader.h"
#include "shaderManager.h"


////////////////
// CLASS Leap //
////////////////

/**
 * @brief Leap Motion wrapper.
 */
class LIB_API Leap: public Node
{
	//////////
public: //
	//////////

		// Const/dest:	 
	Leap(const std::string&, glm::mat4);
	~Leap();

	// Init/free:
	bool init();
	bool free();

	// Polling:
	bool update();
	const LEAP_TRACKING_EVENT* getCurFrame() const;

	/**
	 * \brief Renders the leap object.
	 *
	 * This function is called to render the leap object in the scene.
	 *
	 * \param coords The matrix representing the camera position.
	 */
	void render(glm::mat4 coords) override;

	/**
	 * \brief Build the spheres representing the hands.
	 */
	void buildHands();

	/**
	 * \brief Set collision callback
	 */
	void setCollisionCallback(void(*callback)(void*));


	///////////	 
private:	//
	///////////			

	   // Leap Motion:
	LEAP_CONNECTION connection;
	LEAP_DEVICE_REF leapDevice;
	LEAP_TRACKING_EVENT curFrame;
	signed long long lastFrameId;

	/**
	 * \var m_vertices
	 * \brief The vertices representing the position of the sphere composing the leap hands.
	 *
	 * m_vertices is a member variable that holds the position of the spheres that compose the two hands
	 */
	std::vector<glm::vec3> m_vertices;

	unsigned int m_vertex_vbo = 0;
	unsigned int m_vao = 0;

	/**
	 * \brief Callback for handling collisions
	 */
	void (*collision_callback)(void*);
};
