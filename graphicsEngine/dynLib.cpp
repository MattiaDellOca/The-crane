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
bool MyEngine::initFlag = false;
MyEngine* MyEngine::myEngine = nullptr;


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



////////////////////////////
// BODY OF CLASS MyEngine //
////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initialization method. Call this before any other function.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::init(const char* name, int width, int height)
{
   // Prevent double init:
   if (initFlag)
   {
      std::cout << "ERROR: class already initialized" << std::endl;
      return false;
   }
   // flags:
   initFlag = true;
   myEngine = new MyEngine();

   // Init FreeGLUT/GL content:
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(width, height);

   // FreeGLUT can parse command-line params, in case:
   //FIXME maybe there is a better solution for glutInit
   char fakeParam[] = "fake";
   char* fakeargv[] = { fakeParam, NULL };
   int fakeargc = 1;

   glutInit(&fakeargc, fakeargv);

   // Set some optional flags:
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

   // Create the window with a specific title:   
   glutCreateWindow(name);

   // The OpenGL context is now initialized...

   //Z buffer
   glEnable(GL_DEPTH_TEST);

   std::cout << "OpenGL context" << std::endl;
   std::cout << "   version  . . : " << glGetString(GL_VERSION) << std::endl;
   std::cout << "   vendor . . . : " << glGetString(GL_VENDOR) << std::endl;
   std::cout << "   renderer . . : " << glGetString(GL_RENDERER) << std::endl;
   std::cout << "[Graphics Engine initialized]" << std::endl;

   return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Deinitialization method.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::free()
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   // Done:
   initFlag = false;
   
   // Closing OpenGL

   // Set null singleton
   myEngine = nullptr;

   std::cout << "[Graphics Engine terminated]" << std::endl;
   return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setting Keyboard callback.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::setKeyboardCallback(void (*func)(unsigned char key, int mouseX, int mouseY))
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   glutKeyboardFunc(func);

   std::cout << "[KeyboardCallback setted]" << std::endl;
   return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setting backgroud color.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::setBackgroundColor(float r, float g, float b, float a)
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   // Global OpenGL settings:
   glClearColor(r,g,b,a);

   std::cout << "[Background setted]" << std::endl;
   return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Clear OpenGL window.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::clearWindow()
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }
   //Clear screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Clear Z Buffer
   glClearDepth(1);

   std::cout << "[Window cleared]" << std::endl;
   return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Swap front and back buffer.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::swapBuffers()
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   // Swap this context's buffer:     
   glutSwapBuffers();

   std::cout << "[Buffers swapped]" << std::endl;
   return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * do something.
 * @return true on success, false on error
 */
bool LIB_API MyEngine::doSomething()
{
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }
   glutMainLoop();

   //DrawCube

   // Init face colors:
   unsigned char colors[6][3];

   for (int c = 0; c < 6; c++)
      for (int d = 0; d < 3; d++)
         colors[c][d] = rand() % 255;


   // Back:
   glBegin(GL_TRIANGLE_STRIP);         //FRONT SQUARE
   glColor3f(colors[0][0], colors[0][1], colors[0][2]);
   glVertex3f(-10.0f, -10.0f, 10.0f);   //bottom left
   glVertex3f(10.0f, -10.0f, 10.0f);    //bottom right
   glVertex3f(-10.0f, 10.0f, 10.0f);    //top left
   glVertex3f(10.0f, 10.0f, 10.0f);     //top right
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);         //TOP SQUARE
   glColor3f(colors[1][0], colors[1][1], colors[1][2]);
   glVertex3f(-10.f, 10.f, 10.f);       //bottom left
   glVertex3f(10.f, 10.f, 10.f);        //bottom right
   glVertex3f(-10.f, 10.f, -10.f);      //top left
   glVertex3f(10.f, 10.f, -10.f);       //to right
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);         //BOTTOM SQUARE
   glColor3f(colors[2][0], colors[2][1], colors[2][2]);
   glVertex3f(-10.f, -10.f, 10.f);
   glVertex3f(10.f, -10.f, 10.f);
   glVertex3f(-10.f, -10.f, -10.f);
   glVertex3f(10.f, -10.f, -10.f);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);         //RIGHT SQUARE
   glColor3f(colors[3][0], colors[3][1], colors[3][2]);
   glVertex3f(10.f, -10.f, 10.f);
   glVertex3f(10.f, 10.f, 10.f);
   glVertex3f(10.f, -10.f, -10.f);
   glVertex3f(10.f, 10.f, -10.f);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);         //LEFT SQUARE
   glColor3f(colors[4][0], colors[4][1], colors[4][2]);
   glVertex3f(-10.f, -10.f, 10.f);
   glVertex3f(-10.f, 10.f, 10.f);
   glVertex3f(-10.f, -10.f, -10.f);
   glVertex3f(-10.f, 10.f, -10.f);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);         //BACK SQUARE
   glColor3f(colors[5][0], colors[5][1], colors[5][2]);
   glVertex3f(-10.0f, -10.0f, -10.0f);
   glVertex3f(10.0f, -10.0f, -10.0f);
   glVertex3f(-10.0f, 10.0f, -10.0f);
   glVertex3f(10.0f, 10.0f, -10.0f);
   glEnd();

   std::cout << "[Buffers swapped]" << std::endl;
   return true;
}
