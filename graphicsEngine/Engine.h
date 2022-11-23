#pragma once
/**
 * @file         engine.h
 * @brief        An OpenGL-based graphic engine .dll/.so dynamic library
 *
 */
 /////////////
 // VERSION //
 /////////////
        // Generic info:
#define LIB_NAME      "GraphicsEngine v0.1a"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)
#ifdef _WINDOWS         
   // Export API:
   // Specifies i/o linkage (VC++ spec):
#ifdef GRAPHICSENGINE_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif              
#else // Under Linux
#define LIB_API  // Dummy declaration
#endif
/////////////
// CLASSES //
/////////////
#include "node.h"
#include "camera.h"
#include <functional>

/**
 * @brief Simple static class example.
 */
class LIB_API Engine {
private:
	Node* m_scene_graph;

	Engine() : m_scene_graph{nullptr} {};
	~Engine() {
		delete m_scene_graph;
	}
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

