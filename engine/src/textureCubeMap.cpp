#include "textureCubeMap.h"

#include <GL/glew.h>
#include "FreeImage.h"


LIB_API TextureCubeMap::TextureCubeMap(const std::string& name, const std::string& dir_path, const std::string cubemapNames[6]) : Texture(name), m_dir_path{ dir_path },
m_cubemap_names{ cubemapNames[0], cubemapNames[1], cubemapNames[2], cubemapNames[3], cubemapNames[4], cubemapNames[5] } {
	// Lazy loading of textures
	m_loaded = false;

	// Append this object to the m_textures list
	m_textures.push_back(this);
};

LIB_API TextureCubeMap::~TextureCubeMap() {

}

void LIB_API TextureCubeMap::render(glm::mat4 coords) {
	if (!m_loaded || m_reload_request) {
		// If already loaded, delete texture
		if (m_loaded && m_reload_request) {
			glDeleteTextures(1, &m_texture_id);
		}

		// Reload from file
		loadTexture(&m_texture_id);

		// Set loaded to true if false
		if (!m_loaded)
			m_loaded = true;
		// Reset reload request if was requested
		if (m_reload_request)
			m_reload_request = false;
	}

	// bind the texture object to the current texture unit
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
}

void LIB_API TextureCubeMap::loadTexture(unsigned int* textureID) {
    // Create and bind cubemap:   
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
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
        std::string path = m_dir_path + m_cubemap_names[curSide];
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