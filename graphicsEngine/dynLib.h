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
   static bool init(int*, char**);
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
