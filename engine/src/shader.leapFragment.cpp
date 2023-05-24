static const char* leapFragShader = R"(
   #version 440 core
   
   uniform vec3 color;   
   out vec4 frag_Output;
   
   void main(void)
   {      
      frag_Output = vec4(color, 1.0f);
   }
)";