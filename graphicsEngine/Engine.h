#pragma once

//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "Node.h"
#include "Camera.h"


/////////////
// CLASSES //
/////////////

class Engine {
private:
	Node* m_scene_graph;

	Engine() {};
public:
	static Engine* getInstance();
	void init(int* argc, char** argv);
	Node* load(std::string);
	void clear();
	void begin3D(Camera);
	void end3D();
	void swap();
	void free();

	// Callback setters
	void setKeyboardFunction(void (*callback)(unsigned char, int, int));
	void setDisplayFunction(void (*callback)());
	void setReshapeFunction(void (*callback)(int, int));
	void setSpecialKeyboardFunction(void (*callback)(int, int, int));
};