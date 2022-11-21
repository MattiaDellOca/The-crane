/**
 * @file         dynLib.cpp
 * @brief        A simple .dll/.so dynamic library
 *
 */
 //////////////
 // #INCLUDE //
 //////////////
   // Library main include:
#include "dynLib.h"

   //C/C++:
#include <iostream>

   //GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


   //FreeGLUT:
#include <GL/freeglut.h>


////////////
// STATIC //
////////////

   // Reserved pointer:
bool DynLib::initFlag = false;


//////////////
// DLL MAIN //
//////////////
#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
   // Check use:
   switch (reason)
   {
      ///////////////////////////
   case DLL_PROCESS_ATTACH: //
      break;
      ///////////////////////////
   case DLL_PROCESS_DETACH: //
      break;
   }
   // Done:
   return true;
}
#endif
//////////////////////////
// BODY OF CLASS DynLib //
//////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initialization method. Call this before any other Eureka function.
 * @return true on success, false on error
 */
bool LIB_API DynLib::init()
{
   // Prevent double init:
   if (initFlag)
   {
      std::cout << "ERROR: class already initialized" << std::endl;
      return false;
   }
   // Done:
   initFlag = true;
   return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Deinitialization method.
 * @return true on success, false on error
 */
bool LIB_API DynLib::free()
{
   // Really necessary?
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   // Done:
   initFlag = false;
   return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Simple, useless method.
 * @return true on success, false on error
 */
bool LIB_API DynLib::doNothing()
{
   // Probably excessive checking:
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }
   // FIXME: Test GLM
   glm::vec3 vec(glm::vec3(1, 2, 3));
   std::cout << "If you read this, your library is working as expected!" << std::endl;
   std::cout << "GLM TEST: " << glm::to_string(vec) << std::endl;

   // Done:
   return true;
}
