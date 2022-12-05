//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "engine.h"
#include "perspectiveCamera.h"

	// C/C++
#include <iostream>
#include <thread>


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
Node* Engine::m_scene_graph = nullptr;
RenderingList* Engine::m_rendering_list = new RenderingList{"Rendering list"};
bool Engine::m_initFlag = false;
bool Engine::m_isRunning = false;
int Engine::m_window_height = -1;
int Engine::m_window_width = -1;
int Engine::m_windowId = NULL;
Camera* Engine::m_curr_camera = nullptr;

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


/////////////
// PRIVATE //
/////////////


Engine::Engine() {};
Engine::~Engine() {
	delete m_scene_graph;
	delete m_rendering_list;
}

/* Add a node to the rendering list:
*  if the node has children, had them recursively 
*/
void Engine::passNode(Node* node) {
	std::cout << "Loading " << node->getName() << " in rendering list" << std::endl;
	m_rendering_list->pass(node);
	if (node->getNumberOfChildren() > 0) {
		// pass each child
		for (auto* c : node->getChildren()) {
			passNode(c);
		}
	}
}


void Engine::reshapeCallback(int width, int height) {
	std::cout << "[Reshape callback called] -> " << width << "x" << height << std::endl;

	// Update viewport size:
	glViewport(0, 0, width, height);

	// Width + Height fields
	m_window_width = width;
	m_window_height = height;

	// If current camera is set, update width / height
	if (m_curr_camera != nullptr) {
		m_curr_camera->updateWindowSize(width, height);
	}
}

void Engine::displayCallback() {
	std::cout << "DISPLAY CALLBACK" << std::endl;
}



////////////
// PUBLIC //
////////////


/**
 * Initialization method. Call this before any other Eureka function.
 * @return true on success, false on error
 */
bool LIB_API Engine::init(const char* title, unsigned int width, unsigned int height, int* argc, char** argv)
{
	// Prevent double init:
	if (m_initFlag)
	{
		std::cout << "ERROR: Engine already initialized" << std::endl;
		return false;
	}
	// Set flag
	m_initFlag = true;

	std::cout << "Initializing engine" << std::endl;
	std::cout << std::endl;
	glutInit(argc, argv); // FIXME: Should we pass parameters?
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// FreeGLUT init
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Global OpenGL settings:
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

	// Enable Z-Buffer+Lighting+Face Cûlling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	glutInitWindowPosition(500, 500);

	// Set window size
	m_window_width = width;
	m_window_height = height;
	glutInitWindowSize(width, height);
	
	// Create the window with a specific title:
	m_windowId = glutCreateWindow(title);

	// Set reshape function
	glutReshapeFunc(reshapeCallback);
	
	// Set running state
	m_isRunning = true;

	// Succes!!
	return true;
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
void LIB_API Engine::begin3D(Camera* camera) {
	// Save camera
	m_curr_camera = camera;
	// Pass to right coordinates based on requested camera
	glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(camera->getMatrix()));
	glMatrixMode(GL_MODELVIEW);
}

/**
* Stop drawing
*/
void LIB_API Engine::end3D() {
	glEnd();

	// Clear camera
	m_curr_camera = nullptr;
}


/**
* Swap back-buffer and front-buffer to show current render result
*/
void LIB_API Engine::swapBuffers() {
	// Swap back buffer <-> front buffer
	glutSwapBuffers();
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

	// Done:
	m_initFlag = false;
	return true;
}


void LIB_API Engine::render() {
	std::cout << std::endl;
	std::cout << "RENDERING Scene Graph..." << std::endl;
	
	// Start rendering
	if (m_scene_graph != nullptr) {
		// Clear rendering list
		m_rendering_list->clear();

		std::cout << "Loading nodes..." << std::endl;
		
		if (m_curr_camera == nullptr) {
			std::cout << "[ENGINE] Warning: trying to render not in a begin-end block. Skip frame rendering." << std::endl;
			return;
		}

		// Popolate rendering list
		m_rendering_list->setCamera(m_curr_camera);
		passNode(m_scene_graph);

		// Order rengering list
		m_rendering_list->sort();

		std::cout << "Rendering nodes..." << std::endl;
		
		// Render
		m_rendering_list->render();
	}
	else {
		std::cout << "[ENGINE] WARNING: Scene graph not initialized" << std::endl;
	}
	

	// force refresh
	glutPostRedisplay();
}

void LIB_API Engine::run(void (*renderFunction)()) {
	glutDisplayFunc(renderFunction);
	glutMainLoop();

	// Stopped running, set m_isRunning to false
	m_isRunning = false;
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


bool LIB_API Engine::isRunning() {
	return m_isRunning;
}

void LIB_API Engine::load(Node* newScene) {
	m_scene_graph = newScene;
}

