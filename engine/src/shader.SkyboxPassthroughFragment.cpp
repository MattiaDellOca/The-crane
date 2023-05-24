static const char* skyboxPassthroughFragShader = R"(
   #version 440 core
   
   in vec3 texCoord;
   
   // Texture mapping (cubemap):
   layout(binding = 0) uniform samplerCube cubemapSampler;

   out vec4 fragOutput;

   void main(void)
   {       
      fragOutput = texture(cubemapSampler, texCoord);
   }
)";