#include "ShaderManager.h"
#include <iostream>

// Initialize static map
std::map<std::string, Shader*> ShaderManager::shaders;

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
   return shaders[name];
}

void LIB_API ShaderManager::free() {
   for (auto it = shaders.begin(); it != shaders.end(); ++it) {
		delete it->second;
	}
	shaders.clear();
}