// Header:
#include "skybox.h"
// Glew:
#include <GL/glew.h>
// FreeImage:
#include <FreeImage.h>
#include<iostream>

LIB_API Skybox::Skybox(const std::string& name, const std::string& dirPath, const std::string cubemapNames[6]) : Node(name, glm::mat4(1.0f)) {
    buildCube();
    texture = new TextureCubeMap{ "skybox cubemap textures", dirPath, cubemapNames };
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

    texture->render(glm::mat4(1.0f));

    // Render the mesh using VAO
    glDisable(GL_CULL_FACE);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
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