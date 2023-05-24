#pragma once

#include "lib.h"
#include "object.h"
#include "texture.h"
#include <vector>

/**
 * \class Texture2D
 * \brief A class for rendering 2D textures.
 *
 * The Texture2D is derived from the Texture class
 */
class LIB_API Texture2D : public Texture {
public:
    /**
     * \brief Constructor for the Texture2D class.
     *
     * \param name The name of the texture.
     * \param file_path The path to the image file to use for the texture.
     */
    Texture2D(const std::string& name, const std::string& file_path);

    /**
    * \brief Deconstructor.
    */
    ~Texture2D();

    /**
   * \brief Copy constructor for the Texture2D class.
   *
   * \param o The Texture2D object to copy.
   */
    Texture2D(const Texture2D& o) = delete;

    /**
    * \brief Copy assignment operator for the Texture2D class.
    *
    * \param o The Texture2D object to copy.
    * \returns A reference to the Texture2D object.
    */
    Texture2D& operator=(const Texture2D& o) = delete;

    /**
    * \brief Move constructor for the Texture2D class.
    *
    * \param o The Texture2D object to move.
    */
    Texture2D(Texture2D&& o) = delete;

    /**
    * \brief move assignment operator for the Texture2D class.
    *
    * \param o The Texture2D object to move.
    * \returns A reference to the Texture2D object.
    */
    Texture2D& operator=(Texture2D o) = delete;


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
     * \brief Generate a whyte 1x1 texture to use as default.
     */
    void generateDefaultTexture();

    /**
     * \var m_default_texture_id
     * The ID of the default texture.
     */
    static unsigned int m_default_texture_id;
};