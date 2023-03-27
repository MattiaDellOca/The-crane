#pragma once

#include "shader.h"

class ShaderWrapper {
public:
	static Shader* shader;

	// WARING: temporarly, must be removed!
	static Shader* passthroughShader;
};