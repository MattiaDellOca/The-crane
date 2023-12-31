#pragma once

#include "shader.h"
#include "lib.h"
#include <map>

/**
 * 
 * \class ShaderManager
 * \brief A static class that manages Shader objects.
 *This class provides a static interface for managing Shader objects.
 * It allows for adding and retrieving Shader objects by name and creating new Shader objects.
*/
class LIB_API ShaderManager {
public:
   /**
   * Get a Shader by name.
   * \param name The name of the Shader.
   * \return A pointer to the Shader object if found, nullptr otherwise.
   */
   static Shader* getShader(std::string name);

   /**
   * Create a new Shader.
   * \param name The name to give the new Shader.
   * \return A pointer to the new Shader object.
   */
   static Shader* createShader(const std::string& name);

   /**
   * Free all Shader objects and clear the ShaderManager.
   */
   static void free();

   /**
   * Set the active Shader.
   * \param name The name of the Shader.
   */
   static void setActiveShader(std::string name);


   /**
   * Get the active Shader.
   */
   static Shader* getActiveShader();

private:
   static std::map<std::string, Shader*> shaders;
   static std::string activeProgramShader;
};