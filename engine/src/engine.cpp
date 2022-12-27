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
	
	//FreeImage:
#include "FreeImage.h"

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
bool Engine::m_render_wireframe = false;
EngineGraphics* Engine::m_graphics_settings = nullptr;

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
	FreeImage_DeInitialise();
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



////////////
// PUBLIC //
////////////

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
	
	// Init context
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 500);
	
	m_window_width = width;
	m_window_height = height;
	glutInitWindowSize(width, height);

	// FreeGLUT init
	glutInit(argc, argv);

	// Global OpenGL settings:
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
	
	// Create the window with a specific title:
	m_windowId = glutCreateWindow(title);
	
	// Enable Z-Buffer+Lighting+Face Culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// Set reshape function
	glutReshapeFunc(reshapeCallback);

	// Init FreeImage for texture mapping
	FreeImage_Initialise();
	
	// Set running state
	m_isRunning = true;

	// Succes!!
	return true;
}

void LIB_API Engine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
}


void LIB_API Engine::toggleWireframe() {
	m_render_wireframe = !m_render_wireframe;
	if (m_render_wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void LIB_API Engine::begin3D(Camera* camera) {
	// Save camera
	m_curr_camera = camera;
	// Pass to right coordinates based on requested camera
	
	glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(camera->getProperties()));
	glMatrixMode(GL_MODELVIEW);
	
}


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
	
	// Start rendering
	if (m_scene_graph != nullptr) {
		// Clear rendering list
		m_rendering_list->clear();
		
		if (m_curr_camera == nullptr) {
			std::cout << "[ENGINE] WARNING: trying to render not in a begin-end block. Skip frame rendering." << std::endl;
			return;
		}

		// Popolate rendering list: the second parameter is an idetity matrix because the "pass" function is recursive and
		// need the matrix of the parent node when rendering its child. Since "root" has no parent, pass an identity matrix instead
		m_rendering_list->pass(m_scene_graph, glm::mat4(1));
		
		// Render
		m_rendering_list->render(m_curr_camera->getMatrix());
	}
	else {
		std::cout << "[ENGINE] WARNING: Scene graph not initialized" << std::endl;
		return;
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

void LIB_API Engine::setSpecialKeyboardFunction(void (*callback)(int,int,int))
{
	glutSpecialFunc(callback);
}

void LIB_API Engine::setKeyboardFunction(void (*callback)(unsigned char,int,int)) {
	glutKeyboardFunc(callback);
}


bool LIB_API Engine::isRunning() {
	return m_isRunning;
}

// Load scene graph given a .ovo file
void LIB_API Engine::load(std::string path, std::string texturesDir) {

	// Check if the path ends with a '\\' sequence
	if (texturesDir.back() != '\\') {
		// Add a '\\' sequence to the end of the path
		texturesDir += "\\";
	}

	Ovoreader ovoreader;
	m_scene_graph = ovoreader.readFile(path.c_str(), texturesDir.c_str());
}

void LIB_API Engine::setGraphics(EngineGraphics& g) {
	// Save new configuration
	m_graphics_settings = &g;

	// Apply settings
	Texture::setFilter(g.filter, g.mipmap);
	Texture::setTextureWrap(g.wrap);

	// If anisotropicFiltering is enabled
	if (g.useAnisotropicFiltering) {
		try {
			Texture::enableAnisotropicFiltering(g.anisotropicFilteringValue);
		}
		catch (std::invalid_argument ex) {
			std::cout << "WARNING: Error while enabling anisotropic filtering. " << ex.what() << std::endl;

			// Disable anisotropic filtering
			Texture::disableAnisotropicFiltering();
		}
	}
	else {
		Texture::disableAnisotropicFiltering();
	}
}
