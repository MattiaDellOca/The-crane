#pragma once

/////////////////////////
// DISABLE DLL WARNING //
/////////////////////////
#pragma warning(disable: 4251)

/////////////
// VERSION //
/////////////
       // Generic info:
#define LIB_NAME      "GraphicsEngine"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)
#ifdef _WINDOWS         
   // Export API:
   // Specifies i/o linkage (VC++ spec):
#ifdef ENGINE_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif              
#else // Under Linux
#define LIB_API  // Dummy declaration
#endif