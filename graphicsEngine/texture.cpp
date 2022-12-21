#include "texture.h"

	//C/C++
#include <iostream>

	//GLM:
#include <glm/gtc/type_ptr.hpp>

	//FreeGLUT:
#include <GL/freeglut.h>

	//FreeImage:
#include <FreeImage.h>

LIB_API Texture::Texture(std::string name, std::string path) : Object{ name } {
	// Load texture from filepath
	glGenTextures(1, &m_texId);

	// Load image
	m_data = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str());

	// Load height + width
	m_height = FreeImage_GetHeight((FIBITMAP*)m_data);
	m_width = FreeImage_GetWidth((FIBITMAP*)m_data);
};

LIB_API Texture::~Texture() {
	// Destroy texture
	glDeleteTextures(1, &m_texId);
	FreeImage_Unload((FIBITMAP*)m_data);
}

/// <summary>
/// Load texture from m_data bitmap
/// </summary>
void LIB_API Texture::load() {
	if (m_data != nullptr) {
		// Bind to current texture
		glBindTexture(GL_TEXTURE_2D, m_id);
		
		// Set parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits((FIBITMAP*)m_data));
	}
	else {
		std::cout << "[ENGINE] Warning: cannot load texture, bitmap data is not set" << std::endl;
	}
}