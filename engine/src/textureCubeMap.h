#pragma once

#include "texture.h"

/**
 * \class TextureCubeMap
 * \brief A class for rendering cube map textures.
 *
 * The TextureCubeMap is derived from the Texture class
 */
class LIB_API TextureCubeMap : public Texture {
public:
    /**
     * \brief Constructor for the TextureCubeMap class.
     *
     * \param name The name of the texture.
     * \param dir_path The path to the directory containing the textures.
     * \param cubemapNames The names of the image files used for the textures.
     */
    TextureCubeMap(const std::string& name, const std::string& dir_path, const std::string* cubemapNames);

    /**
    * \brief Deconstructor.
    */
    ~TextureCubeMap();

    /**
   * \brief Copy constructor for the Texture2D class.
   *
   * \param o The Texture2D object to copy.
   */
    TextureCubeMap(const TextureCubeMap& o) = delete;

    /**
    * \brief Copy assignment operator for the Texture2D class.
    *
    * \param o The Texture2D object to copy.
    * \returns A reference to the Texture2D object.
    */
    TextureCubeMap& operator=(const TextureCubeMap& o) = delete;

    /**
    * \brief Move constructor for the Texture2D class.
    *
    * \param o The Texture2D object to move.
    */
    TextureCubeMap(TextureCubeMap&& o) = delete;

    /**
    * \brief move assignment operator for the Texture2D class.
    *
    * \param o The Texture2D object to move.
    * \returns A reference to the Texture2D object.
    */
    TextureCubeMap& operator=(TextureCubeMap o) = delete;


    /**
     * \brief Renders the texture.
     *
     * \param coords UNUSED.
     */
    virtual void render(glm::mat4 coords) override;
private:
    /**
     * \brief Loads a texture either from an image file or by using the default one.
     *
     * \param textureId A pointer to the texture ID to store the result.
     */
    void loadTexture(unsigned int* textureId) override;

    /**
     * \var m_textures_path
     * The path to the directory containing the textures.
     */
    std::string m_dir_path;

    /**
     * \var m_cubemap_names
     * The names of the image files used for the textures.
     */
    std::string m_cubemap_names[6];
};