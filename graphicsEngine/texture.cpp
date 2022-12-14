#include "texture.h"

	//C/C++
#include <iostream>

	//GLM:
#include <glm/gtc/type_ptr.hpp>

   //FreeGLUT:
#include <GL/freeglut.h>


LIB_API Texture::Texture(std::string name, std::string path) : Object{name} {
	// Load texture from filepath
	glGenTextures(1, &m_texId);

	// Load bitmap data from file path

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