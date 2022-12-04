#pragma once

#include "lib.h"
#include "camera.h"
#include "object.h"
#include "mesh.h"
#include "light.h"

#include <iterator>
#include <vector>
#include <list>

class LIB_API RenderingList : public Object {
protected:
	std::list<Node> *m_list;		// objects contained can be either Meshes or Lights: generalization to Node
	Camera *m_camera;				// Camera is has a pure virtual function, therefore it can't be initialized
public:
	RenderingList(std::string);
	std::list<Node>* getRenderingList();
	void setCamera(Camera *);
	void pass(Node);
	void sort();
	void render();
};
