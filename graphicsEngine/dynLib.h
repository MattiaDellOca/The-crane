#pragma once
/**
 * @file         dynLib.h
 * @brief        A simple .dll/.so dynamic library
 *
 */
#pragma once
 /////////////
 // VERSION //
 /////////////
        // Generic info:
#define LIB_NAME      "Dynamic Library v0.1a"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)
#ifdef _WINDOWS         
   // Export API:
   // Specifies i/o linkage (VC++ spec):
#ifdef GRAPHICSENGINE_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif              
#else // Under Linux
#define LIB_API  // Dummy declaration
#endif
/////////////
// CLASSES //
/////////////
/**
 * @brief Simple static class example.
 */
class LIB_API DynLib
{
   //////////
public:    //
   //////////           
   
  // Init/free:
   static bool init();
   static bool free();   
   // Event manager:
   static bool doNothing();
   ///////////
private:    //
   ///////////           
   
   // Const/dest (as private to prevent instanciation):
   DynLib() {};
   ~DynLib() {}
   
   // Internal vars:
   static bool initFlag;
};


/**
* @brief Main graphicals engine class
*/
class LIB_API MyEngine
{
   //////////
public:    //
   //////////           
   
   // Singleton:
   MyEngine(MyEngine& other) = delete; //copy constructor
   void operator=(const MyEngine&) = delete; //assignment operator

   // Init/free:
   static bool init(const char* , int, int);
   static bool free();

   // Callback manager:
   static bool setKeyboardCallback(void (*func)(unsigned char, int, int)); //point to a function with parameters char, int, int

   // Funcionalities:
   static bool setBackgroundColor(float, float, float, float = 1.f);
   static bool clearWindow();
   static bool swapBuffers();
   static bool doSomething(); //FIXME

   ///////////
protected:  //
   ///////////   

   static MyEngine* myEngine; //singleton instance

   ///////////
private:    //
   ///////////           
   
   // Const/dest (as private to prevent instanciation):
   MyEngine() {}
   ~MyEngine() {}

   // Internal vars:
   static bool initFlag;
   
};