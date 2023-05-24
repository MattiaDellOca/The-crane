static const char* fragShaderOmniDirectionalLight = R"(
   #version 440 core
	
   out vec4 fragOutput;

	// Uniforms:
   uniform vec3 fog;

	// Varying:
   in vec3 normal;
   in vec4 fragPosition;
   in float dist;
   in vec2 texCoord;	

   // Texture mapping:
   layout(binding = 0) uniform sampler2D texSampler;

	// nr lights
	uniform int nrLights;

   // Material properties:
   uniform vec3 matEmission;
   uniform vec3 matAmbient;
   uniform vec3 matDiffuse;
   uniform vec3 matSpecular;
   uniform float matShininess;

   // Light properties:
   uniform vec3 lightPosition; 
   uniform vec3 lightAmbient; 
   uniform vec3 lightDiffuse; 
   uniform vec3 lightSpecular;
	uniform float lightAttenuationConstant;
	uniform float lightAttenuationLinear;
	uniform float lightAttenuationQuadratic;



   void main(void)
   {
      // Texture element:
      vec4 texel = texture(texSampler, texCoord);

      // Ambient term:
      vec3 fragColor = (matEmission + matAmbient * lightAmbient) / nrLights;
		
      // Diffuse term:
      vec3 _normal = normalize(normal);
      vec3 lightDirection = normalize(lightPosition - fragPosition.xyz);      
		float distance = length(lightPosition - fragPosition.xyz);
		float attenuation = 1.0 / (lightAttenuationConstant + lightAttenuationLinear * distance + lightAttenuationQuadratic * (distance * distance));

      float nDotL = dot(lightDirection, _normal);   
      if (nDotL > 0.0f)
      {
         fragColor += matDiffuse * nDotL * lightDiffuse;
      
         // Specular term:
         vec3 halfVector = normalize(lightDirection + normalize(-fragPosition.xyz));                     
         float nDotHV = dot(_normal, halfVector);         
			fragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular;
      } 
      
		// Attenuation term:
		fragColor = fragColor * attenuation;

      // Final color:
      //fragOutput = texel * vec4(mix(fragColor, fog , dist), 1.0f);
      fragOutput = texel * vec4(fragColor, 1.0f);
   }
)";