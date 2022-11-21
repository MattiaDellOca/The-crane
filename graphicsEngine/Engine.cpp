//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "Engine.h"

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


/////////////
// CLASSES //
/////////////

Engine* Engine::getInstance() {
	static Engine* m_instance;
	if (!m_instance)
		m_instance = new Engine();
		
	return m_instance;
}

void Engine::init(int* argc, char** argv) {
	std::cout << "Initializing engine" << std::endl;
	std::cout << std::endl;

	// Init context:
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	// FreeGLUT can parse command-line params, in case:
	glutInit(argc, argv); // FIXME: Should we pass parameters?

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Global OpenGL settings:
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

	// Enable Z-Buffer+Lighting+Face Cûlling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	/*
	glutInitWindowPosition(500, 500);
	

	// Set some optional flags:

	// Create the window with a specific title:
	windowId = glutCreateWindow("OGL lighting");

	// Set callback functions:
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialCallback);

	
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);

	// Enter the main FreeGLUT processing loop:
	glutMainLoop();

	// Done:
	return 0;
	*/
}

Node* Engine::load(std::string) {
	std::cout << "Function load still needs to be implemented!" << std::endl;
	return nullptr;
}

void Engine::clear() {
	std::cout << "Function clear still needs to be implemented!" << std::endl;
}

void Engine::begin3D(Camera camera) {
	std::cout << "Function begin3D still needs to be implemented!" << std::endl;
}

void Engine::end3D() {
	std::cout << "Function end3D still needs to be implemented!" << std::endl;
}

void Engine::swap() {
	std::cout << "Function swap still needs to be implemented!" << std::endl;
}

void Engine::free() {
	std::cout << "Function free still needs to be implemented!" << std::endl;
}

//
// Callback setters
//
void Engine::setDisplayFunction(void (*callback)())
{
	glutDisplayFunc(callback);
}

void Engine::setReshapeFunction(void (*callback)(int,int))
{
	glutReshapeFunc(callback);
}

void Engine::setSpecialKeyboardFunction(void (*callback)(int,int,int))
{
	glutSpecialFunc(callback);
}

void Engine::setKeyboardFunction(void (*callback)(unsigned char,int,int)) {
	glutKeyboardFunc(callback);
}


