#include "texture.h"

#include <cstring>
#include <iostream>
#include <stdexcept> 
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "FreeImage.h"

#include <fstream>

Filter LIB_API Texture::m_settings_filter = Filter::NEAREST;
TextureMipmap LIB_API Texture::m_settings_mipmap = TextureMipmap::_DISABLED;
TextureWrap LIB_API Texture::m_settings_wrap = TextureWrap::REPEAT;
bool LIB_API Texture::m_settings_dirty = false;
std::vector<Texture*> LIB_API Texture::m_textures{};

LIB_API Texture::Texture(const std::string& name, const std::string& file_path) : Object(name), m_file_path(file_path), m_loaded{ false } {
	// Lazy loading of textures
	m_loaded = false;

	// Append this object to the m_textures list
	m_textures.push_back(this);
};

LIB_API Texture::~Texture() {
	// Remove this texture from the m_textures vector
	for (int i = 0; static_cast<unsigned int>(i) < m_textures.size(); i++) {
		if (this->m_id == m_textures.at(i)->m_id) {
			m_textures.erase(m_textures.begin() + i);
		}
	}

	// delete texture
	glDeleteTextures(1, &m_texture_id);
}

void LIB_API Texture::setFilter(Filter f, TextureMipmap mipmap)
{
	if (f == LINEAR) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (mipmap == MIPMAP_LINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else if (mipmap == MIPMAP_NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		}
		else if (mipmap == _DISABLED) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else {
			// UNKNOWN VALUE
			throw std::invalid_argument("Mipmap setting not supported, unkown value");
		}
	}
	else if (f == NEAREST) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (mipmap == MIPMAP_LINEAR) {
			throw std::invalid_argument("Linear mapping (MIPMAP_LINEAR) is not possibile with NEAREST filter");
		}
		else if (mipmap == MIPMAP_NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
		else if (mipmap == _DISABLED) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else {
			// UNKNOWN VALUE
			throw std::invalid_argument("Mipmap setting not supported, unkown value");
		}
	}
	else {
		// Unknown filter
		throw std::invalid_argument("Filter setting not supported, unkown value");
	}

	// Check if reload is needed (when activating mipmapping), skip if it's the first time interacting with graphics settings (will be automatically loaded correctly on "render" call)
	if (m_settings_dirty && m_settings_mipmap != mipmap) {
		// Cycle through the list of created textures and set the "m_reload_request" flag to true
		for (Texture* t : m_textures) {
			t->m_reload_request = true;
		}
	}

	// Update fields
	m_settings_filter = f;
	m_settings_mipmap = mipmap;

	// Check dirty flag
	if (!m_settings_dirty) {
		m_settings_dirty = true;
	}
}

void LIB_API Texture::setTextureWrap(TextureWrap wrap) {
	// Texture wrap
	if (wrap == REPEAT) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (wrap == CLAMP_TO_EDGE) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	// Update settings
	m_settings_wrap = wrap;
}

void LIB_API Texture::enableAnisotropicFiltering(unsigned int level)
{
	// Check if supported
	if (strstr(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)), "GL_EXT_texture_filter_anisotropic")) {
		// Check if level is supported
		int maxAntisotropicLevel;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAntisotropicLevel);

		// Set new level if possible
		if (level <= static_cast<unsigned int>(maxAntisotropicLevel)) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, level);
		}
		else {
			throw std::invalid_argument{ "Chosen anisotropic level value exceeded maximum supported value. Maximum possible value: " + std::to_string(level) };
		}
	}
	else {
		throw std::invalid_argument{ "Anisotropic filtering not supported." };
	}
}

void LIB_API Texture::disableAnisotropicFiltering() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
}
