#pragma once

#include "object.h"

class LIB_API Texture : public Object {
private:
	unsigned int m_texId;
	unsigned int m_height;
	unsigned int m_width;
	void* m_data;
public:
	Texture(std::string name, std::string path);
	~Texture();

	void load();
};