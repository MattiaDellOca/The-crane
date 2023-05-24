static const char* vertShader = R"(
   #version 440 core

   // Uniforms:
   uniform mat4 projection;
   uniform mat4 modelview;
   uniform mat3 normalMatrix;
   uniform float farPlane;

	// Attributes:
   layout(location = 0) in vec3 in_Position;
   layout(location = 1) in vec3 in_Normal;
   layout(location = 2) in vec2 in_TexCoord;

	// Varying:
   out vec3 normal;
   out vec4 fragPosition;
   out vec2 texCoord;
   out float dist;

   void main(void)
   {
      fragPosition = modelview * vec4(in_Position, 1.0f);
      gl_Position = projection * fragPosition;
	  dist = abs(gl_Position.z / farPlane);
      normal = normalMatrix * in_Normal;
      texCoord = in_TexCoord;
   }
)";