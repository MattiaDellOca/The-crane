static const char* fragShaderSpotLight = R"(
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

	// nr light
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
	uniform vec3 lightDirection; // The direction of the spot light
	uniform float lightCutoff; // The angle of the spot light cone in degrees
	uniform float lightExponent; // The exponent for the spot light falloff
	
	void main(void)
	{
    // Texture element:
    vec4 texel = texture(texSampler, texCoord);

    //  Ambient term
    vec3 ambient = lightAmbient * matAmbient;
    
    // Diffuse term
    vec3 lightDir = normalize(lightPosition - fragPosition.xyz);
    float cosTheta = dot(lightDir, normalize(normal));
    vec3 diffuse = vec3(0.0);
    if (cosTheta > 0.0) {
        diffuse = lightDiffuse * matDiffuse * cosTheta;
    }
    
    // Specular term
    vec3 specular = vec3(0.0);
    vec3 viewDir = normalize(-fragPosition.xyz);
    vec3 reflectDir = reflect(-lightDir, normalize(normal));
    float cosPhi = dot(viewDir, reflectDir);
    if (cosTheta > 0.0 && cosPhi > 0.0) {
        specular = lightSpecular * matSpecular * pow(cosPhi, matShininess);
    }
    
    // Calculate the spot light:
    vec3 spotLight = vec3(0.0);
    float cosAngle = dot(-lightDirection, lightDir);
    if (cosAngle > cos(radians(lightCutoff))) {
        float spotFactor = pow(cosAngle, lightExponent);
        spotLight = lightDiffuse * matDiffuse * spotFactor;
    }
    
    // Combine the lights and apply fog:
    vec3 fragColor = (matEmission / nrLights + ambient / nrLights + diffuse + specular + spotLight);
    //fragOutput = texel * vec4(mix(fragColor, fog, dist), 1.0);
    fragOutput = texel * vec4(fragColor, 1.0);
	}
)";