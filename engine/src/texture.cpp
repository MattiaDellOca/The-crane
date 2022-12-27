#include "texture.h"

#include <iostream>
#include <GL/freeglut.h>
#include "FreeImage.h"

LIB_API Texture::Texture(std::string name, std::string file_path) : Object(name) {
    // Load file path using FreeImage
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file_path.c_str(), 0), file_path.c_str());
    if (bitmap == nullptr) {
        throw std::runtime_error("Error: Failed to load image from file: " + file_path);
    }

    // Now extract info
    unsigned int width = FreeImage_GetWidth(bitmap);
    unsigned int height = FreeImage_GetHeight(bitmap);
    BYTE* data = FreeImage_GetBits(bitmap);

    // Generate a new texture
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load into OpenGL texture infos
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
    
    // free the .DDS and RGBA images
    FreeImage_Unload(bitmap);
};

LIB_API Texture::~Texture() {
    // delete texture
    glDeleteTextures(1, &m_texture_id);
}

void LIB_API Texture::render(glm::mat4 coords) {
    // bind the texture object to the current texture unit
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}