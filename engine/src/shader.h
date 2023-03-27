#pragma once



//////////////
// #INCLUDE //
//////////////

// Project classes
#include "object.h"

// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C/C++:
#include <iostream>



////////////
// CLASS  //
////////////

/**
 * \brief OGL Shader. Management and rendering of shaders.
 */
class LIB_API Shader : public Object
{
   //////////
public: //
   //////////

      // Constants:
   static const unsigned int MAX_LOGSIZE = 4096;  ///< Max output size in char for a shader log

   // Enums:
   enum ///< Kind of shader
   {
      TYPE_UNDEFINED = 0,
      TYPE_VERTEX,
      TYPE_FRAGMENT,
      TYPE_PROGRAM,
      TYPE_LAST
   };

   // Const/dest:	 
   Shader(const std::string& name);
   ~Shader();

   // Get/set:
   int getParamLocation(const char* name);
   inline void setMatrix(int param, const glm::mat4& mat);
   inline void setMatrix3(int param, const glm::mat3& mat);
   inline void setFloat(int param, float value);
   inline void setInt(int param, int value);
   inline void setVec3(int param, const glm::vec3& vect);
   inline void setVec4(int param, const glm::vec4& vect);
   // Accessing data:
   bool loadFromMemory(int kind, const char* data);
   bool loadFromFile(int kind, const char* filename);
   bool build(Shader* vertexShader, Shader* fragmentShader);

   inline void bind(int location, const char* attribName);

   // Rendering:				
   bool render(void* data = nullptr);

   /**
   * \brief Renders the node and its children.
   * \param coords The pre-computed world coordinates of the node.
   */
   void virtual render(glm::mat4 coords) override;

   ///////////	 
private:	//
   ///////////					

      // Object kind:
   int type;

   // OGL id:
   unsigned int glId;
};