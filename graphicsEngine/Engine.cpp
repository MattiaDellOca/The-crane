//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "engine.h"

	// C/C++
#include <iostream>


// FIXME: HERE OR IN DYNLIB? WE NEED TO DISCUSS THIS
   //GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


   //FreeGLUT:
#include <GL/freeglut.h>

////////////
// STATIC //
////////////

	// Reserved pointer:
bool Engine::m_initFlag = false;
bool Engine::m_isRunning = false;
Engine* Engine::m_instance = nullptr;
int Engine::m_windowId = NULL;

//////////////
// DLL MAIN //
//////////////
#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
	switch (reason)
	{
		///////////////////////////
	case DLL_PROCESS_ATTACH: //
		break;
		///////////////////////////
	case DLL_PROCESS_DETACH: //
		break;
	}
	// Done:
	return true;
}
#endif

/**
 * Initialization method. Call this before any other Eureka function.
 * @return true on success, false on error
 */
bool LIB_API Engine::init(const char* title, unsigned int width, unsigned int height)
{
	// Prevent double init:
	if (m_initFlag)
	{
		std::cout << "ERROR: class already initialized" << std::endl;
		return false;
	}
	// Set flag
	m_initFlag = true;

	std::cout << "Initializing engine" << std::endl;
	std::cout << std::endl;

	// Init context:
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// FreeGLUT init
	glutInit(0, NULL); // FIXME: Should we pass parameters?

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Global OpenGL settings:
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

	// Enable Z-Buffer+Lighting+Face Cûlling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	glutInitWindowPosition(500, 500);
	glutInitWindowSize(width, height);

	// Create the window with a specific title:
	m_windowId = glutCreateWindow(title);

	// Enter the main FreeGLUT processing loop:
	// glutMainLoop();

	return true;
}

/**
 * Deinitialization method.
 * @return true on success, false on error
 */
bool LIB_API Engine::free()
{
	// Really necessary?
	if (!m_initFlag)
	{
		std::cout << "ERROR: class not initialized" << std::endl;
		return false;
	}

	// Delete Engine instance
	delete m_instance;

	// Done:
	m_initFlag = false;
	return true;
}


/**
* Get Engine instance
* @return Engine instance
*/
Engine* Engine::getInstance() {
	if (!m_instance) {
		m_instance = new Engine();
	}
	return m_instance;
}

/**
* Clear buffers
*/
void LIB_API Engine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
}

/**
* Start drawing something
*/
void LIB_API Engine::begin3D(Camera camera) {
	std::cout << "Function begin3D still needs to be implemented!" << std::endl;
}

/**
* Stop drawing
*/
void LIB_API Engine::end3D() {
	std::cout << "Function end3D still needs to be implemented!" << std::endl;
}

/**
* Swap back-buffer and front-buffer to show current render result
*/
void LIB_API Engine::swapBuffers() {
	// Swap back buffer <-> front buffer
	glutSwapBuffers();
}


void LIB_API Engine::render() {
	std::cout << "RENDERING Scene Graph..." << std::endl;
}


bool LIB_API Engine::isRunning() {
	return m_isRunning;
}

//
// Callback setters
//

/**
* Set special keyboard callback
*/
void LIB_API Engine::setSpecialKeyboardFunction(void (*callback)(int,int,int))
{
	glutSpecialFunc(callback);
}

/**
* Set keyboard callback
*/
void LIB_API Engine::setKeyboardFunction(void (*callback)(unsigned char,int,int)) {
	glutKeyboardFunc(callback);
}
