#pragma once
/**
 * @file         engine.h
 * @brief        An OpenGL-based graphic engine .dll/.so dynamic library
 *
 */

/////////////
// CLASSES //
/////////////
#include "camera.h"
#include "lib.h"

/**
 * @brief Simple static class example.
 */
class LIB_API Engine {
private:
	Node* m_scene_graph;

	Engine();
	~Engine();
	static bool m_initFlag;
	static Engine* m_instance;
	static bool m_isRunning;
	static int m_windowId;
	static void reshapeCallback(int, int);
	static void displayCallback();
public:
	static Engine* getInstance();
	static bool init(const char*, unsigned int, unsigned int, int*, char**);
	static Node* load(std::string);
	static void clear();
	static void setBackgroundColor(float, float, float);
	static void begin3D(Camera*);
	static void end3D();
	static void swapBuffers();
	static bool free();
	static void render();

	static void run(void (*)());


	// Callback setters
	static void setKeyboardFunction(void (*callback)(unsigned char, int, int));
	static void setSpecialKeyboardFunction(void (*callback)(int, int, int));
	
	// Utility
	static bool isRunning();
};

