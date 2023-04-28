// Header:
#include "skybox.h"

// Glew:
#include <GL/glew.h>

// FreeImage:
#include <FreeImage.h>

#include<iostream>


LIB_API Skybox::Skybox(const std::string& name, const std::string& texturesPath, const std::string cubemapNames[6]) : Node(name, glm::mat4(1)), m_textures_path{texturesPath},
    m_cubemap_names{ cubemapNames[0], cubemapNames[1], cubemapNames[2], cubemapNames[3], cubemapNames[4], cubemapNames[5] } {
    buildCube();
    buildCubemap();
}

LIB_API Skybox::~Skybox() {
    glDeleteBuffers(1, &m_vertex_vbo);
    glDeleteBuffers(1, &m_texture_vbo);
    glDeleteBuffers(1, &m_face_index_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void LIB_API Skybox::render(glm::mat4 matrix) {
    // Keep only camera rotation
    matrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


    // Load modelview matrix
    ShaderManager::setActiveShader("Skybox Passthrough Program Shader");
    Shader* progShader = ShaderManager::getActiveShader();
    progShader->setMatrix(progShader->getParamLocation("modelview"), matrix);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Render the mesh using VAO
    glDisable(GL_CULL_FACE);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void LIB_API Skybox::buildCube() {
    float cubeVertices[] = // Vertex and tex. coords are the same
    {
       -1.0f,  1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
    };
    
    // Face indexes
    unsigned short cubeFaces[] =
    {
       0, 1, 2,
       0, 2, 3,
       3, 2, 6,
       3, 6, 7,
       4, 0, 3,
       4, 3, 7,
       6, 5, 4,
       7, 6, 4,
       4, 5, 1,
       4, 1, 0,
       1, 5, 6,
       1, 6, 2,
    };

    // Init VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Load cube data into a VBO:
    glGenBuffers(1, &m_vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 8, cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_face_index_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_face_index_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3 * 12, cubeFaces, GL_STATIC_DRAW);
    
    // Unbind the VAO
    glBindVertexArray(0);
    
}

void LIB_API Skybox::buildCubemap() {
    // Create and bind cubemap:   
    glGenTextures(1, &m_cubemap_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap_id);

    // Set params:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Set filters:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load sides:
    for (int curSide = 0; curSide < 6; curSide++)
    {
        // Load texture:
        std::string path = m_textures_path + m_cubemap_names[curSide];
        FIBITMAP* fBitmap = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str());
        if (fBitmap == nullptr)
            std::cout << "[ERROR] loading file '" << m_cubemap_names[curSide] << "'" << std::endl;
        int intFormat = GL_RGB;
        GLenum extFormat = GL_BGR;
        if (FreeImage_GetBPP(fBitmap) == 32)
        {
            intFormat = GL_RGBA;
            extFormat = GL_BGRA;
        }

        // Fix mirroring:
        FreeImage_FlipHorizontal(fBitmap);  // Correct mirroring from cube's inside
        FreeImage_FlipVertical(fBitmap);    // Correct JPG's upside-down

        // Send texture to OpenGL:
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + curSide, 0, intFormat, FreeImage_GetWidth(fBitmap), FreeImage_GetHeight(fBitmap), 0, extFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fBitmap));

        // Free resources:
        FreeImage_Unload(fBitmap);
    }
}