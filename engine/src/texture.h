#pragma once

#include "lib.h"
#include "object.h" // include the header for the Object class

// Texture class derived from Object
class LIB_API Texture : public Object {
public:
    // constructor with name and path to image file
    Texture(std::string name, std::string file_path);
    // Texture(std::string name, std::string file_path, clampToEdge, useAnisotropic);
    ~Texture();

    // Render
    virtual void render(glm::mat4 coords);
private:
    unsigned int m_texture_id;
    
    bool clampToEdge = false;
    bool useAnisotropic = false;
};