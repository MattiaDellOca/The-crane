#include "ovoreader.h"

Node LIB_API* Ovoreader::readFile(char* path) {
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


	/////////////////
	// Parse chuncks:	
	unsigned int chunkId, chunkSize;
	while (true) {
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
		switch ((OvObject::Type)chunkId) {

			case OvObject::Type::OBJECT:
				parseOject(data, &position);
				break;


			case OvObject::Type::NODE:
				unsigned int nChildren;
				parseNode(data, &position, &nChildren);
				break;
		}
	}
}



void Ovoreader::parseOject(char* data, unsigned int* position) {
	cout << "version]" << endl;

	// OVO revision number:
	unsigned int versionId;
	memcpy(&versionId, data + *position, sizeof(unsigned int));
	cout << "   Version . . . :  " << versionId << endl;
	position += sizeof(unsigned int);
}

Node* Ovoreader::parseNode(char* data, unsigned int* position, unsigned int* nChildren) {
	cout << "node]" << endl;

	// Node name:
	char nodeName[FILENAME_MAX];
	strcpy(nodeName, data + *position);
	cout << "   Name  . . . . :  " << nodeName << endl;
	position += (unsigned int)strlen(nodeName) + 1;

	// Node matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + *position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Nr. of children nodes:
	memcpy(nChildren, data + *position, sizeof(unsigned int));
	cout << "   Nr. children  :  " << nChildren << endl;
	position += sizeof(unsigned int);

	// Optional target node, [none] if not used:
	char targetName[FILENAME_MAX];
	strcpy(targetName, data + *position);
	cout << "   Target node . :  " << targetName << endl;
	position += (unsigned int)strlen(targetName) + 1;

	Node* node = new Node{ nodeName, matrix };
	return node;
}