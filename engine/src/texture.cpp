#include "texture.h"

#include <iostream>
#include <GL/freeglut.h>
#include "FreeImage.h"

Filter LIB_API Texture::m_settings_filter = Filter::NEAREST;
TextureMipmap LIB_API Texture::m_settings_mipmap = TextureMipmap::_DISABLED;
TextureWrap LIB_API Texture::m_settings_wrap = TextureWrap::REPEAT;
bool LIB_API Texture::m_needs_reload = false;

LIB_API Texture::Texture(std::string name, std::string file_path) : Object(name), m_file_path(file_path), m_loaded{ false } {
    // Load texture from file
    if (loadTexture(file_path, &m_texture_id)) {
        m_loaded = true;
    }
    else {
        throw std::runtime_error{ "The texture file cannot be read" };
    }
};

LIB_API Texture::~Texture() {
    // delete texture
    glDeleteTextures(1, &m_texture_id);
}

void LIB_API Texture::render(glm::mat4 coords) {
    if (!m_loaded || m_needs_reload) {
        // If already loaded, delete texture
        if (m_loaded && m_needs_reload) {
            glDeleteTextures(1, &m_texture_id);
        }

        // Reload from file
        loadTexture(m_file_path, &m_texture_id);

        // Set loaded to true
        m_loaded = true;
        // Reset need reload field
        m_needs_reload = false;
    }
    else {
        // bind the texture object to the current texture unit
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }
}

void LIB_API Texture::setFilter(Filter f, TextureMipmap mipmap)
{
    bool reloadNeeded = false;
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

    // Update fields
    m_settings_filter = f;
    m_settings_mipmap = mipmap;
}

bool LIB_API Texture::loadTexture(std::string file, unsigned int* textureID) {
    // Load file path using FreeImage
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file.c_str(), 0), file.c_str());
    if (bitmap == nullptr) {
        return false;
    }

    // Now extract info
    unsigned int width = FreeImage_GetWidth(bitmap);
    unsigned int height = FreeImage_GetHeight(bitmap);
    BYTE* data = FreeImage_GetBits(bitmap);

    // Generate a new texture
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);

    // Check if mipmap is enabled
    if (Texture::m_settings_mipmap != _DISABLED) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
    }

    // free the .DDS and RGBA images
    FreeImage_Unload(bitmap);

    // Success
    return true;
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
    if (strstr((const char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic")) {
        // Check if level is supported
        int maxAntisotropicLevel;
        glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAntisotropicLevel);
        
        // Set new level if possible
        if (level <= maxAntisotropicLevel) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, level);
        }
        else {
            throw std::invalid_argument{ "Chosen anisotropic level value exceeded maximum supported value. Maximum possible value: " + std::to_string(level)};
        }
    }
    else {
        throw std::invalid_argument{ "Anisotropic filtering not supported." };
    }
}

void LIB_API Texture::disableAnisotropicFiltering() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
}
