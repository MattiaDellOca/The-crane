#pragma once

//////////////
// #INCLUDE //
//////////////  

   // GLM:   
#define GLM_FORCE_CTOR_INIT         // Constructors no longer init to identity since 0.9.9
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>

// C/C++:
#include <vector>   
#include <map>
#include <iostream>
#include <iomanip>   
#include <limits.h>

using namespace std;

#include "lib.h"
#include "node.h"
#include "material.h"
#include "mesh.h"
#include "light.h"
#include "directionalLight.h"
#include "omnidirectionalLight.h"
#include "positionalLight.h"
#include "spotLight.h"
#include "lightType.h"
#include "vertex.h"


/////////////
// #DEFINE //
/////////////

   // General:
#define APP_NAME "OVO Reader v0.8.1r"

// Macro for printing an OvMatrix4 to console:   
#define MAT2STR(m) std::cout << "   Matrix  . . . :  \t" << m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t" << m[3][0] << std::endl \
                           << "                    \t" << m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\t" << m[3][1] << std::endl \
                           << "                    \t" << m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\t" << m[3][2] << std::endl \
                           << "                    \t" << m[0][3] << "\t" << m[1][3] << "\t" << m[2][3] << "\t" << m[3][3] << std::endl 


/////////////
// CLASSES //
/////////////

/**
 * Stripped-down redefinition of OvObject (just for the chunk IDs).
 */
class LIB_API OvObject {
public:
    /**
     * OvObject subtypes enum.
     */
    enum class Type : int  ///< Type of entities
    {
        // Foundation types:
        OBJECT = 0,
        NODE,
        OBJECT2D,
        OBJECT3D,
        LIST,

        // Derived classes:
        BUFFER,
        SHADER,
        TEXTURE,
        FILTER,
        MATERIAL,
        FBO,
        QUAD,
        BOX,
        SKYBOX,
        FONT,
        CAMERA,
        LIGHT,
        BONE,
        MESH,	   // Keep them...
        SKINNED, // ...consecutive        
        INSTANCED,
        PIPELINE,
        EMITTER,

        // Animation type
        ANIM,

        // Physics related:
        PHYSICS,

        // Terminator:
        LAST,
    };
};

/**
 * Stripped-down redefinition of OvMesh (just for the subtypes).
 */
class LIB_API OvMesh
{
public:
    /**
     * OvMesh subtypes enum.
     */
    enum class Subtype : int ///< Kind of mesh
    {
        // Foundation types:
        DEFAULT = 0,
        NORMALMAPPED,
        TESSELLATED,

        // Terminator:
        LAST,
    };
};

/**
 * Stripped-down redefinition of OvLight (just for the subtypes).
 */
class LIB_API OvLight
{
public:
    /**
     * OvLight subtypes enum.
     */
    enum class Subtype : int ///< Kind of light
    {
        // Foundation types:
        OMNI = 0,
        DIRECTIONAL,
        SPOT,

        // Terminator:
        LAST,
    };
};

/**
 * OvoReader class that describes an .ovo 3D models parser.
 */
class LIB_API Ovoreader {
public:
    /**
     * Parse a 3D Ovo model into a scene graph.
     * 
     * \param path Path of the Ovo 3D model file
     * \param texturesDirectory (Optional) Path where textures are stored, default '.\\assets'
     * \return Scene graph that describes the read 3D model
     */
    Node* readFile(const char* path, const char* texturesDir="..\\assets");
protected:
    std::map<string, Material*> m_materials;
    Node* recursiveLoad(FILE* dat, const char* path);
    void parseOject(char* data, unsigned int& position);
    Material* parseMaterial(char* data, unsigned int& position, const char* textureDir);
    Node* parseNode(char* data, unsigned int& position, unsigned int* nChildren);
    Mesh* parseMesh(char* data, unsigned int& position, unsigned int* nChildren);
    Light* parseLight(char* data, unsigned int& position, unsigned int* nChildren);
};