#pragma once

#include "shader.h"
#include "lib.h"
#include <map>

class LIB_API ShaderManager {
public:
   static void AddShader(std::string name, Shader* shader);
   static Shader* GetShader(std::string name);
   static void CreateShader(const std::string& name);

private:
   static std::map<std::string, Shader*> shaders;
};