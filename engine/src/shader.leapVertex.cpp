static const char* leapVertShader = R"(
   #version 440 core

   uniform mat4 projection;
   uniform mat4 modelview;

   layout(location = 0) in vec3 in_Position;

   void main(void)
   {
      gl_Position = projection * modelview * vec4(in_Position, 1.0f);      
   }
)";