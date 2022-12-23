#include "ovoreader.h"

Node LIB_API* Ovoreader::readFile(const char* path) {
	// Open file:
	FILE* dat = fopen(path, "rb");
	if (dat == nullptr)
	{
		cout << "ERROR: unable to open file '" << path << "'" << endl;
		return nullptr;
	}

	// Configure stream:
	cout.precision(2);  // 2 decimals are enough
	cout << fixed;      // Avoid scientific notation


	////////////////////////
	// Parse header chuncks:
    // the first chuncks in a .ovo file are related to the materials used and the version of the file (its tipe is OBJECT).
    // This type don't have children and therefore can't be read with a recursive function
	unsigned int chunkId, chunkSize;
    bool isHeader = true;
	while (isHeader) {
		// Read chunkId and chunkSize while checking if file has ended
		fread(&chunkId, sizeof(unsigned int), 1, dat);
		if (feof(dat))
			break;
		fread(&chunkSize, sizeof(unsigned int), 1, dat);
		cout << "\n[chunk id: " << chunkId << ", chunk size: " << chunkSize << ", chunk type: ";


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
                material = parseMaterial(data, position);
				m_materials.insert(make_pair(material->getName(), material));
				break;

            case OvObject::Type::NODE:
			case OvObject::Type::MESH:
            case OvObject::Type::LIGHT:
            case OvObject::Type::BONE:
            case OvObject::Type::SKINNED:
                // end of header, go recursive
                isHeader = false;
                // this operation is necessary as the first chunk need to be read again in the recursive load, the file offset is
                // set accordingly
                fseek(dat, -1 * (chunkSize + 8), SEEK_CUR);
				break;

            default: 
                cout << "UNKNOWN]" << endl;
                cout << "ERROR: corrupted or bad data in file " << path << endl;
                fclose(dat);
                delete[] data;
                return nullptr;
		}

        // Release chunk memory:
        delete[] data;
	}

    cout << "---------- GOING RECURSIVE ----------" << endl;
    Node* root = recursiveLoad(dat, path);

    // Done:
    fclose(dat);
    cout << "\nFile parsed" << endl;
    return root;
}


Node LIB_API* Ovoreader::recursiveLoad(FILE* dat, const char* path) {
    // Read chunkId and chunkSize while checking if file has ended
    unsigned int chunkId, chunkSize;
    fread(&chunkId, sizeof(unsigned int), 1, dat);
    if (feof(dat))
        return nullptr;
    fread(&chunkSize, sizeof(unsigned int), 1, dat);
    cout << "\n[chunk id: " << chunkId << ", chunk size: " << chunkSize << ", chunk type: ";


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

    case OvObject::Type::BONE:
    case OvObject::Type::SKINNED:
        break;

    default:
        cout << "UNKNOWN]" << endl;
        cout << "ERROR: corrupted or bad data in file " << path << endl;
        fclose(dat);
        delete[] data;
        return nullptr;
    }

    // Release chunk memory:
    delete[] data;


    if (nChildren) {
        while (thisNode->getNumberOfChildren() < nChildren) { 
            Node* childNode = recursiveLoad(dat, path);
            if(childNode != nullptr) 
                thisNode->addChild(childNode);
        }
    }

    return thisNode;
}

void LIB_API Ovoreader::parseOject(char* data, unsigned int& position) {
	cout << "version]" << endl;

	// OVO revision number:
	unsigned int versionId;
	memcpy(&versionId, data + position, sizeof(unsigned int));
	cout << "   Version . . . :  " << versionId << endl;
	position += sizeof(unsigned int);
}

Node LIB_API* Ovoreader::parseNode(char* data, unsigned int& position, unsigned int* nChildren) {
	cout << "node]" << endl;

	// Node name:
	char nodeName[FILENAME_MAX];
	strcpy(nodeName, data + position);
	cout << "   Name  . . . . :  " << nodeName << endl;
	position += (unsigned int)strlen(nodeName) + 1;

	// Node matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

    // Nr. of children nodes:
    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    cout << "   Nr. children  :  " << children << endl;
    *nChildren = children;
    position += sizeof(unsigned int);

	Node* node = new Node{ nodeName, matrix };
	return node;
}

Material LIB_API* Ovoreader::parseMaterial(char* data, unsigned int& position) {
	cout << "material]" << endl;

	// Material name:
	char materialName[FILENAME_MAX];
	strcpy(materialName, data + position);
	cout << "   Name  . . . . :  " << materialName << endl;
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
	float metalness;
	memcpy(&metalness, data + position, sizeof(float));
	position += sizeof(float);

	// Transparency factor:
	float alpha;
	memcpy(&alpha, data + position, sizeof(float));
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

	return material;
}

Mesh LIB_API* Ovoreader::parseMesh(char* data, unsigned int& position, unsigned int* nChildren) {
    cout << "mesh]" << endl;

    // Mesh name:
    char meshName[FILENAME_MAX];
    strcpy(meshName, data + position);
    position += (unsigned int)strlen(meshName) + 1;
    cout << "   Name  . . . . :  " << meshName << endl;

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
    float radius;
    memcpy(&radius, data + position, sizeof(float));
    position += sizeof(float);

    // Mesh bounding box minimum corner:
    glm::vec3 bBoxMin;
    memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Mesh bounding box maximum corner:
    glm::vec3 bBoxMax;
    memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Optional physics properties:
    unsigned char hasPhysics;
    memcpy(&hasPhysics, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

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
                for (unsigned int c = 0; c < nrOfVertices; c++)
                {
                    // Vertex coords:
                    position += sizeof(glm::vec3);
                }
                // Iterate through hull faces:
                for (unsigned int c = 0; c < nrOfFaces; c++)
                {
                    position += sizeof(unsigned int) * 3;
                }
            }
        }
    }


    // Nr. of LODs:
    unsigned int LODs;
    memcpy(&LODs, data + position, sizeof(unsigned int));
    position += sizeof(unsigned int);

    vector<Vertex*> verticesVec;
    Mesh* mesh = new Mesh{ meshName, matrix };

    // For each LOD...:
    vector<unsigned int> verticesPerLOD(LODs); // Let's store this information for the skinned part, in case
    for (unsigned int l = 0; l < 1; l++)
    {
        // Nr. of vertices:
        unsigned int vertices, faces;
        memcpy(&vertices, data + position, sizeof(unsigned int));
        cout << "   Nr. vertices  :  " << vertices << endl;
        position += sizeof(unsigned int);
        verticesPerLOD[l] = vertices;

        // ...and faces:
        memcpy(&faces, data + position, sizeof(unsigned int));
        cout << "   Nr. faces . . :  " << faces << endl;
        position += sizeof(unsigned int);


        // Interleaved and compressed vertex/normal/UV/tangent data:                    
        for (unsigned int c = 0; c < vertices; c++)
        {
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
            unsigned int tangentData;
            memcpy(&tangentData, data + position, sizeof(unsigned int));
            glm::vec4 tangent = glm::unpackSnorm3x10_1x2(tangentData);
            position += sizeof(unsigned int);

            Vertex* v = new Vertex{ vertex, normal, uv, tangent };
            verticesVec.push_back(v);
        }

        // Faces:
        for (unsigned int c = 0; c < faces; c++)
        {
            // Face indexes:
            unsigned int face[3];       // store all points
            memcpy(face, data + position, sizeof(unsigned int) * 3);
            position += sizeof(unsigned int) * 3;

            Vertex* v1 = verticesVec.at(face[0]);
            Vertex* v2 = verticesVec.at(face[1]);
            Vertex* v3 = verticesVec.at(face[2]);

            mesh->addFace(v1, v2, v3);
        }
    }

    auto material = m_materials.find(materialName);
    if (material == m_materials.end()) {
        cout << "ERROR: material '" << materialName << "' doesn't exists in file" << endl;
        return nullptr;
    }

    mesh->setMaterial(material->second);

    return mesh;
}

Light LIB_API* Ovoreader::parseLight(char* data, unsigned int& position, unsigned int* nChildren) {
    cout << "light]" << endl;

    // Light name:
    char lightName[FILENAME_MAX];
    strcpy(lightName, data + position);
    cout << "   Name  . . . . :  " << lightName << endl;
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
    cout << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << endl;
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
    float spotExponent;
    memcpy(&spotExponent, data + position, sizeof(float));
    position += sizeof(float);

    // Cast shadow flag:
    unsigned char castShadows;
    memcpy(&castShadows, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    // Volumetric lighting flag:
    unsigned char isVolumetric;
    memcpy(&isVolumetric, data + position, sizeof(unsigned char));
    position += sizeof(unsigned char);

    Light* light = nullptr;
    glm::vec4 tmp{ color.x, color.y, color.z, 1.0f };
    float attenuation;      // how to calculate this from radius --> http://learnwebgl.brown37.net/09_lights/lights_attenuation.html

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