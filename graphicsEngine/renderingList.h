#pragma once

#include "lib.h"
#include "camera.h"
#include "object.h"
#include "mesh.h"
#include "light.h"

#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

struct RenderNode {
	Node* m_node;
	glm::mat4 m_mat;
};

class LIB_API RenderingList : public Object {
protected:
	std::list<RenderNode *> m_list;
	Camera *m_camera;
public:
	RenderingList(std::string);
	std::list<RenderNode *> getRenderingList();
	void setCamera(Camera *);
	void pass(RenderNode *);
	void clear();
	void render(glm::mat4);
};
