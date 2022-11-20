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
	void init();
	Node* load(std::string);
	void clear();
	void begin3D(Camera);
	void end3D();
	void swap();
	void free();
};