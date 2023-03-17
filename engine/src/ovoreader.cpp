#include "ovoreader.h"

// GLEW
#include <GL/glew.h>

Node LIB_API* Ovoreader::readFile(const char* path, const char* texturesDir) {
	// Open file:
	FILE* dat = fopen(path, "rb");
	if (dat == nullptr)
	{
		cout << "ERROR: unable to open file '" << path << "'" << endl;
		return nullptr;
	}

	////////////////////////
	// Parse header chuncks:
    // the first chuncks in a .ovo file are related to the materials used and the version of the file (its tipe is OBJECT).
    // This types don't have children and therefore can't be read with a recursive function
	unsigned int chunkId, chunkSize;
    bool isHeader = true;
    int rollback = 0;
	while (isHeader) {
		// Read chunkId and chunkSize while checking if file has ended
		fread(&chunkId, sizeof(unsigned int), 1, dat);
		if (feof(dat))
			break;
		fread(&chunkSize, sizeof(unsigned int), 1, dat);


		// Load whole chunk into memory:
		char* data = new char[chunkSize];
		if (fread(data, sizeof(char), chunkSize, dat) != chunkSize)
		{
			cout << "ERROR: unable to read from file '" << path << "'" << endl;
			fclose(dat);
			delete[] data;
			return nullptr;
		}


		// Parse chunk information according to its type:
		unsigned int position = 0;
        Material* material;
		switch ((OvObject::Type)chunkId) {
			case OvObject::Type::OBJECT:
				parseOject(data, position);
				break;

			case OvObject::Type::MATERIAL:
                material = parseMaterial(data, position, texturesDir);
				m_materials.insert(make_pair(material->getName(), material));
				break;

            case OvObject::Type::NODE:
			case OvObject::Type::MESH:
            case OvObject::Type::LIGHT:
            case OvObject::Type::BONE:
            case OvObject::Type::SKINNED:
                // end of header, go recursive
                isHeader = false;

                // Rollback file pointer to the last chunk:
                // this operation is necessary as the last chunk need to be read again in the recursive load
                rollback = -1 * static_cast<int>(chunkSize + 8);
                fseek(dat, rollback, SEEK_CUR);
				break;

            default:
                cout << "ERROR: corrupted or bad data in file " << path << endl;
                fclose(dat);
                delete[] data;
                return nullptr;
		}

        // Release chunk memory:
        delete[] data;
	}

    Node* root = recursiveLoad(dat, path);

    // Done:
    fclose(dat);
    cout << "\nFile OVO parsed" << endl;
    return root;
}

Node LIB_API* Ovoreader::recursiveLoad(FILE* dat, const char* path) {
    // Read chunkId and chunkSize while checking if file has ended
    unsigned int chunkId, chunkSize;
    fread(&chunkId, sizeof(unsigned int), 1, dat);
    if (feof(dat))
        return nullptr;
    fread(&chunkSize, sizeof(unsigned int), 1, dat);


    // Load whole chunk into memory:
    char* data = new char[chunkSize];
    if (fread(data, sizeof(char), chunkSize, dat) != chunkSize)
    {
        cout << "ERROR: unable to read from file '" << path << "'" << endl;
        fclose(dat);
        delete[] data;
        return nullptr;
    }

    // Parse chunk information according to its type:
    unsigned int position = 0;
    unsigned int nChildren = 0;
    Node* thisNode = nullptr;
    switch ((OvObject::Type)chunkId) {
    case OvObject::Type::NODE:
        thisNode = parseNode(data, position, &nChildren);
        break;

    case OvObject::Type::MESH:
        thisNode = parseMesh(data, position, &nChildren);
        break;

    case OvObject::Type::LIGHT:
        thisNode = parseLight(data, position, &nChildren);
        break;

    // This case are not handled, but if objects of this type are present the program won't crash
    case OvObject::Type::BONE:
    case OvObject::Type::SKINNED:
        break;

    // Unkown objects cause the ovoreader to stop
    default:
        cout << "ERROR: corrupted or bad data in file " << path << endl;
        fclose(dat);
        delete[] data;
        return nullptr;
    }

    // Release chunk memory:
    delete[] data;


    // If the node has children, load them
    if (nChildren) {
        while (thisNode->getNumberOfChildren() < nChildren) {
            Node* childNode = recursiveLoad(dat, path);

            // childNode is nullptr when the file has ended
            if(childNode != nullptr)
                thisNode->addChild(childNode);
        }
    }

    // Return root Node
    return thisNode;
}

void LIB_API Ovoreader::parseOject(char* data, const unsigned int& position) {

    // OVO revision number:
    unsigned int versionId;
    memcpy(&versionId, data + position, sizeof(unsigned int));
}

Material LIB_API* Ovoreader::parseMaterial(char* data, unsigned int& position, const char* textureDir) {

    // Material name:
    char materialName[FILENAME_MAX];
    strcpy(materialName, data + position);
    position += (unsigned int)strlen(materialName) + 1;

    // Material term colors, starting with emissive:
    glm::vec3 emission, albedo;
    memcpy(&emission, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Albedo:
    memcpy(&albedo, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Roughness factor:
    float roughness;
    memcpy(&roughness, data + position, sizeof(float));
    position += sizeof(float);

    // Metalness factor:
    position += sizeof(float);

    // Transparency factor:
    position += sizeof(float);

    // Albedo texture filename, or [none] if not used:
    char textureName[FILENAME_MAX];
    strcpy(textureName, data + position);
    position += (unsigned int)strlen(textureName) + 1;

    // Normal map filename, or [none] if not used:
    char normalMapName[FILENAME_MAX];
    strcpy(normalMapName, data + position);
    position += (unsigned int)strlen(normalMapName) + 1;

    // Height map filename, or [none] if not used:
    char heightMapName[FILENAME_MAX];
    strcpy(heightMapName, data + position);
    position += (unsigned int)strlen(heightMapName) + 1;

    // Roughness map filename, or [none] if not used:
    char roughnessMapName[FILENAME_MAX];
    strcpy(roughnessMapName, data + position);
    position += (unsigned int)strlen(roughnessMapName) + 1;

    // Metalness map filename, or [none] if not used:
    char metalnessMapName[FILENAME_MAX];
    strcpy(metalnessMapName, data + position);
    position += (unsigned int)strlen(metalnessMapName) + 1;

    Material* material = new Material{ materialName };
    glm::vec4 tmp{ albedo.x, albedo.y, albedo.z, 1.0f };
    material->setAmbient(tmp * 0.2f);
    material->setDiffuse(tmp * 0.6f);
    material->setSpecular(tmp * 0.4f);
    material->setShininess((1 - sqrt(roughness)) * 128);
    material->setEmission(glm::vec4(emission.x, emission.y, emission.z, 1.0f));

    // Load texture from assets path
    Texture* t = new Texture{textureName, std::string{textureDir} + std::string{textureName} };
    material->setTexture(t);

    return material;
}

Node LIB_API* Ovoreader::parseNode(char* data, unsigned int& position, unsigned int* nChildren) {
	// Node name:
	char nodeName[FILENAME_MAX];
	strcpy(nodeName, data + position);
	position += (unsigned int)strlen(nodeName) + 1;

	// Node matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

    // Nr. of children nodes:
    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    *nChildren = children;
    position += sizeof(unsigned int);

	Node* node = new Node{ nodeName, matrix };
	return node;
}

Mesh LIB_API* Ovoreader::parseMesh(char* data, unsigned int& position, unsigned int* nChildren) {

    // Mesh name:
    char meshName[FILENAME_MAX];
    strcpy(meshName, data + position);
    position += (unsigned int)strlen(meshName) + 1;

    // Mesh matrix:
    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    // Mesh nr. of children nodes:
    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    *nChildren = children;
    position += sizeof(unsigned int);

    // Optional target node, or [none] if not used:
    char targetName[FILENAME_MAX];
    strcpy(targetName, data + position);
    position += (unsigned int)strlen(targetName) + 1;

    // Mesh subtype (see OvMesh SUBTYPE enum):
    unsigned char subtype;
    memcpy(&subtype, data + position, sizeof(unsigned char));
    char subtypeName[FILENAME_MAX];
    switch ((OvMesh::Subtype)subtype)
    {
        case OvMesh::Subtype::DEFAULT: strcpy(subtypeName, "standard"); break;
        case OvMesh::Subtype::NORMALMAPPED: strcpy(subtypeName, "normal-mapped"); break;
        case OvMesh::Subtype::TESSELLATED: strcpy(subtypeName, "tessellated"); break;
        default: strcpy(subtypeName, "UNDEFINED");
    }
    position += sizeof(unsigned char);

    // Material name, or [none] if not used:
    char materialName[FILENAME_MAX];
    strcpy(materialName, data + position);
    position += (unsigned int)strlen(materialName) + 1;

    // Mesh bounding sphere radius:
    position += sizeof(float);

    // Mesh bounding box minimum corner:
    position += sizeof(glm::vec3);

    // Mesh bounding box maximum corner:
    position += sizeof(glm::vec3);

    // Optional physics properties:
    unsigned char hasPhysics;
    memcpy(&hasPhysics, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    // Useless informations, they must be read anyway to set the pointer to the right position
    if (hasPhysics)
    {
        /**
         * Mesh physics properties.
         */
        struct PhysProps
        {
            // Pay attention to 16 byte alignement (use padding):
            unsigned char type;
            unsigned char contCollisionDetection;
            unsigned char collideWithRBodies;
            unsigned char hullType;
            // Vector data:
            glm::vec3 massCenter;
            // Mesh properties:
            float mass;
            float staticFriction;
            float dynamicFriction;
            float bounciness;
            float linearDamping;
            float angularDamping;
            unsigned int nrOfHulls;
            unsigned int _pad;
            // Pointers:
            void* physObj;
            void* hull;
        };
        PhysProps mp;
        memcpy(&mp, data + position, sizeof(PhysProps));
        position += sizeof(PhysProps);
        // Custom hull(s) used?
        if (mp.nrOfHulls)
        {
            for (unsigned int c = 0; c < mp.nrOfHulls; c++)
            {
                // Hull number of vertices:
                unsigned int nrOfVertices;
                memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);
                // Hull number of faces:
                unsigned int nrOfFaces;
                memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);
                // Hull centroid:
                position += sizeof(glm::vec3);
                // Iterate through hull vertices:
                for (unsigned int i = 0; i < nrOfVertices; i++)
                {
                    // Vertex coords:
                    position += sizeof(glm::vec3);
                }
                // Iterate through hull faces:
                for (unsigned int i = 0; i < nrOfFaces; i++)
                {
                    position += sizeof(unsigned int) * 3;
                }
            }
        }
    }


    // Nr. of LODs:
    position += sizeof(unsigned int);
    // Always load only first LOD (level of detail)...:

    // Nr. of vertices:
    unsigned int nVertices, nFaces;
    memcpy(&nVertices, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    // ...and faces:
    memcpy(&nFaces, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    // Allocate VBOs arrays
    float* vertices = new float[nVertices * 3];
    float* normals = new float[nVertices * 3];
    float* textures = new float[nVertices * 2];
    unsigned int* faces = new unsigned int[nFaces * 3];


    // Interleaved and compressed vertex/normal/UV/tangent data:
    for (unsigned int c = 0; c < nVertices; c++) {
        // Vertex coords:
        glm::vec3 vertex;
        memcpy(&vertex, data + position, sizeof(glm::vec3));
        position += sizeof(glm::vec3);

        // Vertex normal:
        unsigned int normalData;
        memcpy(&normalData, data + position, sizeof(unsigned int));
        glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
        position += sizeof(unsigned int);

        // Texture coordinates:
        unsigned int textureData;
        memcpy(&textureData, data + position, sizeof(unsigned int));
        glm::vec2 uv = glm::unpackHalf2x16(textureData);
        position += sizeof(unsigned int);

        // Tangent vector:
        position += sizeof(unsigned int);

        // Populate arrays
        vertices[c * 3] = vertex.x;
        vertices[c * 3 + 1] = vertex.y;
        vertices[c * 3 + 2] = vertex.z;

        normals[c * 3] = normal.x;
        normals[c * 3 + 1] = normal.y;
        normals[c * 3 + 2] = normal.z;

        textures[c * 2] = uv.x;
        textures[c * 2 + 1] = uv.y;
    }

    // Faces:
    // every face is composed by three vertices.
    for (unsigned int c = 0; c < nFaces; c++) {
        // Face indexes:
        unsigned int face[3];       // store all points
        memcpy(face, data + position, sizeof(unsigned int) * 3);
        position += sizeof(unsigned int) * 3;

        faces[c * 3] = face[0];
        faces[c * 3 + 1] = face[1];
        faces[c * 3 + 2] = face[2];
    }

    // Load Material class given the name of the material
    auto material = m_materials.find(materialName);
    if (material == m_materials.end()) {
        cout << "ERROR: material '" << materialName << "' doesn't exists in file" << endl;
        return nullptr;
    }

    // Generate and bind the VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Activate client states
    /*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    */

    // Generate a vertex buffer and bind it
    unsigned int vertexVbo;
    glGenBuffers(1, &vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, nVertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW); // Copy the VBO data from system to video memory
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Generate a normal buffer and bind it
    unsigned int normalVbo;
    glGenBuffers(1, &normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glBufferData(GL_ARRAY_BUFFER, nVertices * 3 * sizeof(float), normals, GL_STATIC_DRAW); // Copy the VBO data from system to video memory
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_TRUE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Generate a texture buffer and bind it
    unsigned int textureVbo;
    glGenBuffers(1, &textureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
    //glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, nVertices * 2 * sizeof(float), textures, GL_STATIC_DRAW); // Copy the VBO data from system to video memory

    // Generate a face buffer and bind it
    unsigned int faceVbo;
    glGenBuffers(1, &faceVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceVbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nFaces * 3 * sizeof(unsigned int), faces, GL_STATIC_DRAW); // Copy the VBO data from system to video memory
    
    // Unbind the VAO
    glBindVertexArray(0);

    // Create mesh
    Mesh* mesh = new Mesh{ meshName, matrix,nFaces, vertexVbo, normalVbo, textureVbo, faceVbo, vao, material->second };

    // Delete unused resources
    delete[] vertices;
    delete[] normals;
    delete[] textures;
    delete[] faces;
    
    return mesh;
}

Light LIB_API* Ovoreader::parseLight(char* data, unsigned int& position, unsigned int* nChildren) {

    // Light name:
    char lightName[FILENAME_MAX];
    strcpy(lightName, data + position);
    position += (unsigned int)strlen(lightName) + 1;

    // Light matrix:
    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    // Nr. of children nodes:
    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    *nChildren = children;
    position += sizeof(unsigned int);

    // Optional target node name, or [none] if not used:
    char targetName[FILENAME_MAX];
    strcpy(targetName, data + position);
    position += (unsigned int)strlen(targetName) + 1;

    // Light subtype (see OvLight SUBTYPE enum):
    unsigned char subtype;
    memcpy(&subtype, data + position, sizeof(unsigned char));
    char subtypeName[FILENAME_MAX];
    switch ((OvLight::Subtype)subtype)
    {
        case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName, "directional"); break;
        case OvLight::Subtype::OMNI: strcpy(subtypeName, "omni"); break;
        case OvLight::Subtype::SPOT: strcpy(subtypeName, "spot"); break;
        default: strcpy(subtypeName, "UNDEFINED");
    }
    position += sizeof(unsigned char);

    // Light color:
    glm::vec3 color;
    memcpy(&color, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Influence radius:
    float radius;
    memcpy(&radius, data + position, sizeof(float));
    position += sizeof(float);

    // Direction:
    glm::vec3 direction;
    memcpy(&direction, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Cutoff:
    float cutoff;
    memcpy(&cutoff, data + position, sizeof(float));
    position += sizeof(float);

    // Exponent:
    position += sizeof(float);

    // Cast shadow flag:
    position += sizeof(unsigned char);

    // Volumetric lighting flag:
    position += sizeof(unsigned char);

    // Generic declaration of Light
    Light* light = nullptr;
    glm::vec4 tmp{ color.x, color.y, color.z, 1.0f };
    float attenuation;      // how to calculate this from radius --> http://learnwebgl.brown37.net/09_lights/lights_attenuation.html

    // Concrete declaration of Light
    switch ((OvLight::Subtype)subtype)
    {
        case OvLight::Subtype::DIRECTIONAL:
            light = new DirectionalLight{ lightName, matrix, tmp, tmp, tmp };
            break;
        case OvLight::Subtype::OMNI:
            attenuation = glm::clamp(10.0f / radius, 0.0f, 1.0f);
            light = new OmnidirectionalLight{ lightName, matrix, tmp, tmp, tmp, 1.0f, attenuation };
            break;
        case OvLight::Subtype::SPOT:
            attenuation = glm::clamp(10.0f / radius, 0.0f, 1.0f);
            light = new SpotLight{ lightName, matrix, tmp, tmp, tmp, cutoff, direction, 1.0f, attenuation };
            break;
    }

    return light;
}
