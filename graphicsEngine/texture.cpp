#include "texture.h"

	//C/C++
#include <iostream>

	//GLM:
#include <glm/gtc/type_ptr.hpp>

	//FreeGLUT:
#include <GL/freeglut.h>

	//FreeImage:
#include <FreeImage.h>

bool Texture::m_is_init = false;

LIB_API Texture::Texture(std::string name, std::string path) : Object{ name } {
	// Load texture from filepath
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);

	// Load bitmap data from file path
	if (!m_is_init) {
		// init freeimage
		FreeImage_Initialise();
		m_is_init = true;
	}

	// Find filename
	std::string tex_filename = path.substr(path.find_last_of("/\\") + 1);
	
	// Load image
	m_data = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), tex_filename.c_str());

	// Load height + width
	m_height = FreeImage_GetHeight(static_cast<FIBITMAP*>(m_data));
	m_width = FreeImage_GetHeight(static_cast<FIBITMAP*>(m_data));
};

LIB_API Texture::Texture(std::string name, unsigned int width, unsigned int height, void* bitmap) : Object{ name }, m_width{ width }, m_height{ height }, m_data { bitmap } {
	// Create and bind texture:
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
};

LIB_API Texture::~Texture() {
	// Destroy texture
	glDeleteTextures(1, &m_texId);
}

/// <summary>
/// Load texture from m_data bitmap
/// </summary>
void LIB_API Texture::load() {
	if (m_data != nullptr) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
	}
	else {
		std::cout << "[ENGINE] Warning: cannot load texture, bitmap data is not set" << std::endl;
	}
}