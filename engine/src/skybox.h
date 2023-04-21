#pragma once

// Project classes
#include "node.h"
#include "shader.h"
#include "shaderManager.h"

// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class LIB_API Skybox : public Node {
private:
    // VAO
	unsigned int m_vertex_vbo = 0;
	unsigned int m_texture_vbo = 0;
    unsigned int m_face_index_vbo = 0;
	unsigned int m_vao = 0;

    // Textures:
    unsigned int m_cubemap_id;
    std::string m_textures_path;
    std::string m_cubemap_names[6];

    /**
    * \brief Instantiate VAO for cube
    */
    void buildCube();

    /**
    * \brief Load cubemap from file
    */
    void buildCubemap();

public:
    Skybox(const std::string&, const std::string&, const std::string*);

    ~Skybox();

    /**
    * \brief Renders the node and its children.
    * \param coords The pre-computed world coordinates of the node.
    */
    virtual void render(glm::mat4) override;
};