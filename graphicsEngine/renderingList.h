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

class LIB_API RenderingList : public Object {
protected:
	std::list<Object *> m_list;
	Camera *m_camera;
	static bool sortCondition(Object *, Object *);
public:
	RenderingList(std::string);
	std::list<Object *> getRenderingList();
	void setCamera(Camera *);
	void pass(Object *);
	void sort();
	void clear();
	void render();
};
