#include "ShaderManager.h"
#include <iostream>
#include <GL/glew.h>

// Initialize static map
std::map<std::string, Shader*> ShaderManager::shaders;
std::string ShaderManager::activeProgramShader;

Shader LIB_API* ShaderManager::GetShader(std::string name) {
   auto it = shaders.find(name);
   if (it != shaders.end()) {
      return it->second;
   }
   else {
      std::cout << "Shader \"" << name << "\" not found in ShaderManager" << std::endl;
      return nullptr;
   }
}

Shader LIB_API* ShaderManager::CreateShader(const std::string& name) {
   shaders[name] = new Shader(name);
   std::cout << "Shader \"" << name << "\" created with id=" << shaders[name]->getId() << std::endl;
   return shaders[name];
}

void LIB_API ShaderManager::free() {
   for (auto it = shaders.begin(); it != shaders.end(); ++it) {
		delete it->second;
	}
	shaders.clear();
}


void LIB_API ShaderManager::setActiveShader(std::string name) {
	activeProgramShader = name;
   getActiveShader()->render();
}

Shader LIB_API* ShaderManager::getActiveShader() {
	return GetShader(activeProgramShader);
}
