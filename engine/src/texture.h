#pragma once

#include "lib.h"
#include "object.h" // include the header for the Object class


/////////////
// #DEFINE //
/////////////

#pragma once

#include "lib.h"
#include "object.h" // include the header for the Object class

/**
 * \def GL_TEXTURE_MAX_ANISOTROPY_EXT
 * Quick define for the extension.
 * See https://www.opengl.org/registry/specs/EXT/texture_filter_anisotropic.txt
 */
#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE

 /**
  * \def GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
  * Quick define for the extension.
  * See https://www.opengl.org/registry/specs/EXT/texture_filter_anisotropic.txt
  */
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF

  // Silly Microsoft GL.h stuck at version 1.1...:
#ifndef GL_CLAMP_TO_EDGE
    #define GL_CLAMP_TO_EDGE 0x812F
#endif

/**
 * \enum Filter
 * Constants for specifying the filter to use when rendering a texture.
 */
enum LIB_API Filter {
    NEAREST,
    LINEAR
};

/**
 * \enum TextureMipmap
 * Constants for specifying the mipmap to use when rendering a texture.
 */
enum LIB_API TextureMipmap {
    _DISABLED,
    MIPMAP_NEAREST,
    MIPMAP_LINEAR
};

/**
 * \enum TextureWrap
 * Constants for specifying the wrap mode to use when rendering a texture.
 */
enum LIB_API TextureWrap {
    REPEAT,
    CLAMP_TO_EDGE
};

/**
 * \class Texture
 * \brief A class for rendering textures.
 *
 * The Texture class is derived from the Object class and is used for rendering
 * textures in an OpenGL program.
 */
class LIB_API Texture : public Object {
public:
    /**
     * \brief Constructor for the Texture class.
     *
     * \param name The name of the texture.
     * \param file_path The path to the image file to use for the texture.
     */
    Texture(std::string name, std::string file_path);

    /**
    * \brief Deconstructor.
    */
    ~Texture();

    /**
     * \brief Renders the texture.
     *
     * \param coords UNUSED.
     */
    virtual void render(glm::mat4 coords);
    
    /**
     * \brief Sets the filter and mipmap to use when rendering textures.
     *
     * \param f The filter to use (NEAREST or LINEAR).
     * \param m The mipmap to use (_DISABLED, MIPMAP_NEAREST, or MIPMAP_LINEAR).
     */
    static void setFilter(Filter f, TextureMipmap m = TextureMipmap::_DISABLED);

    /**
     * \brief Sets the wrap mode to use when rendering textures.
     *
     * \param w The wrap mode to use (REPEAT or CLAMP_TO_EDGE).
     */
    static void setTextureWrap(TextureWrap w);

    /**
     * \brief Enables anisotropic filtering for textures.
     *
     * \param level The level of anisotropic filtering to use (1-16).
     */
    static void enableAnisotropicFiltering(unsigned int level);

    /**
     * \brief Disables anisotropic filtering for textures.
     */
    static void disableAnisotropicFiltering();
private:
    /**
     * \brief Loads a texture from an image file.
     *
     * \param file The path to the image file to use for the texture.
     * \param textureId A pointer to the texture ID to store the result.
     * \returns True if the texture was loaded successfully, false otherwise.
     */
    bool static loadTexture(std::string file, unsigned int* textureId);

    /**
     * \var m_texture_id
     * The ID of the texture.
     */
    unsigned int m_texture_id;

    /**
     * \var m_file_path
     * The path to the image file used for the texture.
     */
    std::string m_file_path;

    /**
     * \var m_loaded
     * Flag indicating whether the texture has been loaded.
     */
    bool m_loaded;

    /**
     * \var m_settings_filter
     * The filter to use when rendering textures.
     */
    static Filter m_settings_filter;
    
    /**
     * \var m_settings_mipmap
     * The mipmap to use when rendering textures.
     */
    static TextureMipmap m_settings_mipmap;

    /**
     * \var m_settings_wrap
     * The wrap mode to use when rendering textures.
     */
    static TextureWrap m_settings_wrap;

    /**
     * \var m_needs_reload
     * Flag indicating whether the textures need to be reloaded.
     */
    static bool m_needs_reload;
};