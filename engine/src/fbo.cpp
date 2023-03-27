
//////////////
// #INCLUDE //
//////////////

// Header:
#include "fbo.h"

// Glew (include it before GL.h):
#include <GL/glew.h>

///////////////////////
// BODY OF CLASS Fbo //
///////////////////////

/**
 * Constructor.
 */
Fbo::Fbo(const std::string& name) : Object(name)
{
	// Init reserved data:
	memset(glRenderBufferId, 0, sizeof(unsigned int) * MAX_ATTACHMENTS);
	for (unsigned int c = 0; c < Fbo::MAX_ATTACHMENTS; c++)
	{
		texture[c] = 0;
		drawBuffer[c] = -1;	// -1 means empty
	}
	nrOfMrts = 0;
	mrt = nullptr;

	// Allocate OGL data:
	glGenFramebuffers(1, &glId);
}

/**
 * Destructor.
 */
Fbo::~Fbo()
{
	// Release reserved data:
	if (mrt)
		delete[] mrt;
	for (unsigned int c = 0; c < Fbo::MAX_ATTACHMENTS; c++)
		if (glRenderBufferId[c])
			glDeleteRenderbuffers(1, &glRenderBufferId[c]);
	glDeleteFramebuffers(1, &glId);
}

/**
 * Get texture connected to buffer #.
 */
unsigned int Fbo::getTexture(unsigned int textureNumber)
{
	if (textureNumber < Fbo::MAX_ATTACHMENTS)
		return texture[textureNumber];
	else
		return 0;
}

/**
 * Check FBO consistency.
 */
bool Fbo::isOk()
{
	// Make FBO current:
	render();

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[ERROR] FBO not complete (error: " << status << ")" << std::endl;
		return false;
	}

	// Done:
	return true;
}

/**
 * Binds a texture to the framebuffer.
 */
bool Fbo::bindTexture(unsigned int textureNumber, unsigned int operation, unsigned int texture, int param1, int param2)
{
	// Safety net:
	if (textureNumber >= Fbo::MAX_ATTACHMENTS)
	{
		std::cout << "[ERROR] Invalid params" << std::endl;
		return false;
	}

	// Bind buffer:
	render();

	// Perform operation:   
	switch (operation)
	{
		//////////////////////////
	case BIND_COLORTEXTURE: //		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + param1, GL_TEXTURE_2D, texture, 0);
		drawBuffer[textureNumber] = param1;
		break;

		//////////////////////////
	case BIND_DEPTHTEXTURE: //
		// glReadBuffer(GL_NONE);
	 // glDrawBuffer(GL_NONE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
		break;

		///////////
	default: //
		std::cout << "[ERROR] Invalid operation" << std::endl;
		return false;
	}

	// Done:
	this->texture[textureNumber] = texture;

	// Get some texture information:
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sizeX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sizeY);
	return updateMrtCache();
}

/**
 * Initializes and binds a render buffer.
 */
bool Fbo::bindRenderBuffer(unsigned int renderBuffer, unsigned int operation, int sizeX, int sizeY)
{
	// Safety net:
	if (renderBuffer >= Fbo::MAX_ATTACHMENTS)
	{
		std::cout << "[ERROR] Invalid params" << std::endl;
		return false;
	}

	// Bind buffer:
	render();

	// If used, delete it first, then create and bind it:
	if (glRenderBufferId[renderBuffer])
		glDeleteRenderbuffers(1, &glRenderBufferId[renderBuffer]);
	glGenRenderbuffers(1, &glRenderBufferId[renderBuffer]);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderBufferId[renderBuffer]);

	// Perform operation:
	switch (operation)
	{
		/////////////////////////
	case BIND_DEPTHBUFFER: //
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, sizeX, sizeY);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, glRenderBufferId[renderBuffer]);
		break;

	default:
		std::cout << "[ERROR] Invalid operation" << std::endl;
		return false;
	}

	// Done:   
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	return updateMrtCache();
}

/**
 * Update the MRT cache.
 */
bool Fbo::updateMrtCache()
{
	// Delete previous buffer:
	if (mrt)
		delete[] mrt;

	// Count targets:   
	nrOfMrts = 0;
	for (unsigned int c = 0; c < Fbo::MAX_ATTACHMENTS; c++)
		if (drawBuffer[c] != -1)
			nrOfMrts++;

	// Refresh buffer:
	if (nrOfMrts)
	{
		mrt = new GLenum[nrOfMrts];
		int bufferPosition = 0;
		for (int c = 0; c < Fbo::MAX_ATTACHMENTS; c++)
			if (drawBuffer[c] != -1)
			{
				mrt[bufferPosition] = GL_COLOR_ATTACHMENT0 + drawBuffer[c];
				bufferPosition++;
			}
	}

	// Done: 
	return true;
}

/**
 * Revert to rendering to the context buffers.
 */
void Fbo::disable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * Fbo rendering procedure.
 */
bool Fbo::render(void* data)
{
	// Bind buffers:
	glBindFramebuffer(GL_FRAMEBUFFER, glId);
	if (nrOfMrts)
	{
		glDrawBuffers(nrOfMrts, mrt);
		glViewport(0, 0, sizeX, sizeY);
	}

	// Done:   
	return true;
}
