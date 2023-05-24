#include "texture2D.h"

#include <GL/glew.h>
#include "FreeImage.h"


unsigned int Texture2D::m_default_texture_id = 0;

LIB_API Texture2D::Texture2D(const std::string& name, const std::string& file_path) : Texture(name), m_file_path{ file_path } {
	if (!m_default_texture_id)
		generateDefaultTexture();

	// Lazy loading of textures
	m_loaded = false;

	// Append this object to the m_textures list
	m_textures.push_back(this);
};

LIB_API Texture2D::~Texture2D() {
	
}

void LIB_API Texture2D::render(glm::mat4 coords) {
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
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void LIB_API Texture2D::generateDefaultTexture() {
	// Generate a new texture
	glGenTextures(1, &m_default_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_default_texture_id);

	// Align to 1 byte
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Allocate an 1x1 bitmap to use as default value and fill it with whyte color
	FIBITMAP* bitmap = FreeImage_Allocate(1, 1, 24);
	BYTE* pixels = FreeImage_GetBits(bitmap);
	pixels[0] = 255; // R
	pixels[1] = 255; // G
	pixels[2] = 255; // B
	int intFormat = GL_RGB;
	GLenum extFormat = GL_BGR;

	// Save texture content
	glTexImage2D(GL_TEXTURE_2D, 0, intFormat, 1, 1, 0, extFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set circular coordinates:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set min/mag filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}


void LIB_API Texture2D::loadTexture(unsigned int* textureID) {
	// If a path is not specified, use default texture
	if (m_file_path == "[none]") {
		m_texture_id = m_default_texture_id;
		return;
	}

	// If a path is specified, read a texture from the specified path
	// Generate a new texture
	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Check if file exists
	std::ifstream fileStream(m_file_path);
	if (!fileStream.good()) {
		throw std::invalid_argument("Texture file does not exist. Check the path.");
	}

	// Check if file type is supported
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(m_file_path.c_str(), 0);
	if (format == FIF_UNKNOWN) {
		throw std::invalid_argument("Texture format not suppoted. List of the supported file types: https://freeimage.sourceforge.io/features.html");
	}

	// Load file path using FreeImage
	FIBITMAP* bitmap = FreeImage_Load(format, m_file_path.c_str());
	if (bitmap == nullptr) {
		throw std::invalid_argument("Error while loading file. Please, check that the file is readable and not corrupted.");
	}

	// If DDS, flip vertically image
	if (format == FIF_DDS) {
		FreeImage_FlipVertical(bitmap);
	}

	// Now extract info
	unsigned int width = FreeImage_GetWidth(bitmap);
	unsigned int height = FreeImage_GetHeight(bitmap);
	BYTE* data = FreeImage_GetBits(bitmap);

	// Check if mipmap is enabled
	if (Texture::m_settings_mipmap != _DISABLED) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, static_cast<void*>(data));
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, static_cast<void*>(data));
	}

	FreeImage_Unload(bitmap);
}