#pragma once

//////////////
// #INCLUDE //
//////////////

// Project classes
#include "object.h"

// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C/C++:
#include <iostream>



////////////
// CLASS  //
////////////

/**
* \class Fbo
* \brief Frame buffer class to deal with OpenGL FBOs.
*/
class LIB_API Fbo : public Object
{
	//////////
public: //
	//////////

	   // Constants:
	static const unsigned int MAX_ATTACHMENTS = 8; ///< Maximum number of available render buffers or textures per FBO	

	// Enumerations:
	enum : unsigned int ///< Kind of operation
	{
		BIND_DEPTHBUFFER = 0,
		BIND_COLORTEXTURE,
		BIND_DEPTHTEXTURE,
	};

	/**
	 * \brief Constructor for the Fbo class.
	 *
	 * \param name The name of the fbo.
	 */
	Fbo(const std::string&);

	/**
	* \brief Deconstructor.
	*/
	~Fbo();

	// Get/set:
	/**
	 * \brief Get texture connected to buffer #.
	 * \param textureNumber texture position
	 * \returns texture glId or 0 if wrong/not available
	 */
	unsigned int getTexture(unsigned int textureNumber);
	inline int getSizeX() { return sizeX; }
	inline int getSizeY() { return sizeY; }
	inline int getSizeZ() { return sizeZ; }
	inline unsigned int getHandle() { return glId; }

	// Management:
	/**
	 * \brief Check FBO consistency.
	 * \returns true on success, false on fail and print error in console
	 */
	bool isOk();

	/**
	 * \brief Binds a texture to the framebuffer.
	 * \param textureNumber a value between 0 and OvFbo::MAX_ATTACHMENTS to identify texture position
	 * \param operation one of the enumerated operations of type OvFbo::BIND_*
	 * \param texture pointer to a texture class
	 * \param param1 free param 1, according to the operation
	 * \param param2 free param 2, according to the operation
	 * \returns true on success, false on fail
	 */
	bool bindTexture(unsigned int textureNumber, unsigned int operation, unsigned int texture, int param1 = 0, int param2 = 0);
	
	/**
	 * \brief Initializes and binds a render buffer.
	 * \param renderBuffer a value between 0 and Fbo::MAX_ATTACHMENTS to identify a render buffer
	 * \param operation one of the enumerated operations of type OvFbo::BIND_*
	 * \param sizeX FBO sizes, make sure to have the same for all attachments
	 * \param sizeY FBO sizes, make sure to have the same for all attachments
	 * \returns true on success, false on fail
	 */
	bool bindRenderBuffer(unsigned int renderBuffer, unsigned int operation, int sizeX, int sizeY);

	// Rendering:    
	/**
	 * \brief Fbo rendering procedure.
	 * \param data generic pointer to instance data
	 * \returns true on success, false on fail
	 */
	bool render(void* data = nullptr);

	/**
	 * \brief Revert to rendering to the context buffers.
	 */
	static void disable();


	///////////
private: //
	///////////

	// Generic data:
	int sizeX, sizeY, sizeZ;	         				///< FBO width, height and depth
	unsigned int texture[MAX_ATTACHMENTS];             ///< Attached textures
	int drawBuffer[MAX_ATTACHMENTS];       		      ///< Set color attachment per texture

	// OGL stuff:
	unsigned int glId;                                 ///< OpenGL ID
	unsigned int glRenderBufferId[MAX_ATTACHMENTS];    ///< Render buffer IDs

	// MRT cache:   
	int nrOfMrts;                                      ///< Number of MRTs
	unsigned int* mrt;                                 ///< Cached list of buffers 

	// Cache:
	/**
	 * \brief Update the MRT cache.
	 * \returns true on success, false on fail
	 */
	bool updateMrtCache();
};