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
#include "renderingList.h"

/**
 * @brief Simple static class example.
 */
class LIB_API Engine {
private:
	Engine();
	~Engine();
	static Node* m_scene_graph;
	static bool m_initFlag;
	static bool m_isRunning;
	static int m_windowId;
	static int m_window_width;
	static int m_window_height;
	static void reshapeCallback(int, int);
	static void displayCallback();
public:
	static bool init(const char*, unsigned int, unsigned int, int*, char**);
	static Node* load(std::string);
	static void load(Node*);
	static void clear();
	static void setBackgroundColor(float, float, float);
	static void begin3D(Camera*);
	static void end3D();
	static void swapBuffers();
	static bool free();
	static void render(Camera*, RenderingList*);
	static void run(void (*)());

	// Callback setters
	static void setKeyboardFunction(void (*callback)(unsigned char, int, int));
	static void setSpecialKeyboardFunction(void (*callback)(int, int, int));
	
	// Utility
	static bool isRunning();
};

