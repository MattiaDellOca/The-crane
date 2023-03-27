//////////////
// #INCLUDE //
//////////////


	// Project classes
#include "engine.h"
#include "perspectiveCamera.h"
#include "shader.h"
#include "shaderWrapper.h"

	// C/C++
#include <iostream>
#include <thread>


   // GLM:
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

	// GLEW:
#include <GL/glew.h>


	// FreeGLUT:
#include <GL/freeglut.h>

	// FreeImage:
#include "FreeImage.h"

/////////////
// #DEFINE //
/////////////

   // Window size:
#define APP_WINDOWSIZEX   1024
#define APP_WINDOWSIZEY   512
#define APP_FBOSIZEX      APP_WINDOWSIZEX / 2
#define APP_FBOSIZEY      APP_WINDOWSIZEY / 1

// Enums:
enum Eye
{
	EYE_LEFT = 0,
	EYE_RIGHT = 1,

	// Terminator:
	EYE_LAST,
};

/////////////
// SHADERS //
/////////////

////////////////////////////
Shader* Engine::vs = nullptr;
Shader* Engine::fs = nullptr;
Shader* Engine::pvs = nullptr;
Shader* Engine::pfs = nullptr;

////////////////////////////
const char* vertShader = R"(
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

////////////////////////////
const char* fragShader = R"(
   #version 440 core
	
   out vec4 fragOutput;

	// Uniforms:
   uniform vec3 fog;

	// Varying:
   in vec3 normal;
   in vec4 fragPosition;
   in float dist;
   in vec2 texCoord;	

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

   // Texture mapping:
   layout(binding = 0) uniform sampler2D texSampler;

   void main(void)
   {
      // Texture element:
      vec4 texel = texture(texSampler, texCoord);

      // Ambient term:
      vec3 fragColor = matEmission + matAmbient * lightAmbient;

      // Diffuse term:
      vec3 _normal = normalize(normal);
      vec3 lightDirection = normalize(lightPosition - fragPosition.xyz);      
      float nDotL = dot(lightDirection, _normal);   
      if (nDotL > 0.0f)
      {
         fragColor += matDiffuse * nDotL * lightDiffuse;
      
         // Specular term:
         vec3 halfVector = normalize(lightDirection + normalize(-fragPosition.xyz));                     
         float nDotHV = dot(_normal, halfVector);         
         fragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular;
      } 
      
      // Final color:
      fragOutput = texel * vec4(mix(fragColor, fog, dist), 1.0f);
   }
)";

////////////////////////////
const char* passthroughVertShader = R"(
   #version 440 core

   // Uniforms:
   uniform mat4 projection;
   uniform mat4 modelview;   

   // Attributes:
   layout(location = 0) in vec2 in_Position;   
   layout(location = 2) in vec2 in_TexCoord;

   // Varying:   
   out vec2 texCoord;

   void main(void)
   {      
      gl_Position = projection * modelview * vec4(in_Position, 0.0f, 1.0f);    
      texCoord = in_TexCoord;
   }
)";

////////////////////////////
const char* passthroughFragShader = R"(
   #version 440 core
   
   in vec2 texCoord;
   
   uniform vec4 color;

   out vec4 fragOutput;   

   // Texture mapping:
   layout(binding = 0) uniform sampler2D texSampler;

   void main(void)   
   {  
      // Texture element:
      vec4 texel = texture(texSampler, texCoord);      
      
      // Final color:
      fragOutput = color * texel;       
   }
)";


////////////
// STATIC //
////////////

// Reserved pointer:
Node* Engine::m_scene_graph = nullptr;
RenderingList* Engine::m_rendering_list = new RenderingList{"Rendering list"};
bool Engine::m_initFlag = false;
bool Engine::m_isRunning = false;
int Engine::m_window_height = -1;
int Engine::m_window_width = -1;
int Engine::m_windowId = -1;
PerspectiveCamera* Engine::m_curr_3Dcamera = nullptr;
OrthographicCamera* Engine::m_curr_2Dcamera = nullptr;
EngineGraphics* Engine::m_graphics_settings = nullptr;
Quad* Engine::m_quad = nullptr;

unsigned int fboTexId[EYE_LAST] = { 0, 0 };
// FBO:      
Fbo* fbo[EYE_LAST] = { nullptr, nullptr };

	// timer function defined by user
void(*userTimerCallback)(int);


//////////////
// DLL MAIN //
//////////////
#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
	switch (reason)
	{
		///////////////////////////
	case DLL_PROCESS_ATTACH: //
		break;
		///////////////////////////
	case DLL_PROCESS_DETACH: //
		break;
	}
	// Done:
	return true;
}
#endif

#ifdef _DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	  
/**
 * Debug message callback for OpenGL. See https://www.opengl.org/wiki/Debug_Output
 */
void __stdcall DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	// Ignore NVIDIA on VBO allocation
	if(id != 131185 && type != 33361)
		std::cout << "OpenGL says: \"" << std::string(message) << "\"" << std::endl;
}
#endif


/////////////
// PRIVATE //
/////////////

Engine::Engine() {};

Engine::~Engine() {
	delete m_scene_graph;
	delete m_rendering_list;
	delete m_curr_2Dcamera;
	delete m_curr_3Dcamera;
	delete m_graphics_settings;
	for (int c = 0; c < EYE_LAST; c++)
	{
		glDeleteTextures(1, &fboTexId[c]);
		delete fbo[c];
	}
	FreeImage_DeInitialise();
}

void Engine::reshapeCallback(int width, int height) {
	std::cout << "[Reshape callback called] -> " << width << "x" << height << std::endl;

	// Update viewport size:
	//glViewport(0, 0, width, height);

	// Width + Height fields
	m_window_width = width;
	m_window_height = height;

	// If current 3D camera is set, update width / height
	if (m_curr_3Dcamera != nullptr) {
		m_curr_3Dcamera->updateWindowSize(width, height);
		std::cout << "[3D] -> " << width << "x" << height << std::endl;

	}

	// If current 2D camera is set, update width / height
	if (m_curr_2Dcamera != nullptr) {
		m_curr_2Dcamera->updateWindowSize(width, height);
		std::cout << "[2D] -> " << width << "x" << height << std::endl;

	}

	// Update viewport size:
	glViewport(0, 0, width, height);

}

void LIB_API Engine::timerCallback(int value) {
	(*userTimerCallback)(value);
	glutTimerFunc(1000, timerCallback, 0);
}

void Engine::buildShaders() {
	// Per pixel lighting shaders
	vs = new Shader("Vertex Shader");
	vs->loadFromMemory(Shader::TYPE_VERTEX, vertShader);
	fs = new Shader("Fragment Shader");
	fs->loadFromMemory(Shader::TYPE_FRAGMENT, fragShader);
	// Setup per pixel lighting shader program:
	ShaderWrapper::shader = new Shader("Program shader");
	ShaderWrapper::shader->build(vs, fs);
	ShaderWrapper::shader->render();
	ShaderWrapper::shader->bind(0, "in_Position");
	ShaderWrapper::shader->bind(1, "in_Normal");
	ShaderWrapper::shader->bind(2, "in_TexCoord");

	// Passthrough shaders
	pvs = new Shader("Passthrough Vertex Shader");
	pvs->loadFromMemory(Shader::TYPE_VERTEX, passthroughVertShader);
	pfs = new Shader("Passthrough Fragment Shader");
	pfs->loadFromMemory(Shader::TYPE_FRAGMENT, passthroughFragShader);
	// Setup per pixel lighting shader program:
	ShaderWrapper::passthroughShader = new Shader("Passthrough Program Shader");
	ShaderWrapper::passthroughShader->build(pvs, pfs);
	ShaderWrapper::passthroughShader->render();
	ShaderWrapper::passthroughShader->bind(0, "in_Position");
	ShaderWrapper::passthroughShader->bind(2, "in_TexCoord");
}

////////////
// PUBLIC //
////////////

bool LIB_API Engine::init(const char* title, unsigned int width, unsigned int height, int* argc, char** argv)
{
	// Prevent double init:
	if (m_initFlag)
	{
		std::cout << "ERROR: Engine already initialized" << std::endl;
		return false;
	}
	// Set flag
	m_initFlag = true;
	std::cout << "Initializing engine" << std::endl;
	std::cout << std::endl;

	// FreeGLUT init
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(4, 4);
	glutInitContextProfile(GLUT_CORE_PROFILE);

#ifdef _DEBUG
	// Enable debug flag
	glutInitContextFlags(GLUT_DEBUG);
	std::cout << "Running in FreeGLUT debugging mode" << std::endl;
#endif
	
	
	// Init FreeGLUT window
	glutInitWindowPosition(100, 100);
	m_window_width = APP_WINDOWSIZEX;
	m_window_height = APP_WINDOWSIZEY;
	glutInitWindowSize(APP_WINDOWSIZEX, APP_WINDOWSIZEY);


	// Global OpenGL settings:
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

	// Create the window with a specific title:
	m_windowId = glutCreateWindow(title);

	// Init Glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cout << "Error while initializing Glew, aborting." << endl;
		return 0;
	}

	// OpenGL 4.4 is required:
	if (!glewIsSupported("GL_VERSION_4_4")) {
		std::cout << "OpenGL 4.4 not supported" << std::endl;
		return 0;
	}

#ifdef _DEBUG
	// Register OpenGL debug callback:
	glDebugMessageCallback((GLDEBUGPROC)DebugCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

	// Enable Z-Buffer+Lighting+Face Culling
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//glEnableClientState(GL_VERTEX_ARRAY);

	// Set reshape function
	glutReshapeFunc(reshapeCallback);

	// Init FreeImage for texture mapping
	FreeImage_Initialise();

	// Set running state
	m_isRunning = true;

	// Build shaders
	buildShaders();
	ShaderWrapper::shader->render();

	// Create quad
	m_quad = new Quad("Quad", m_window_width, m_window_height);

	// Load FBO and its texture:
	GLint prevViewport[4];
	glGetIntegerv(GL_VIEWPORT, prevViewport);

	for (int c = 0; c < EYE_LAST; c++)
	{
		glGenTextures(1, &fboTexId[c]);
		glBindTexture(GL_TEXTURE_2D, fboTexId[c]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, APP_FBOSIZEX, APP_FBOSIZEY, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		fbo[c] = new Fbo("FBO" + c);
		fbo[c]->bindTexture(0, Fbo::BIND_COLORTEXTURE, fboTexId[c]);
		fbo[c]->bindRenderBuffer(1, Fbo::BIND_DEPTHBUFFER, APP_FBOSIZEX, APP_FBOSIZEY);
		if (!fbo[c]->isOk())
			std::cout << "[ERROR] Invalid FBO" << std::endl;
	}
	Fbo::disable();
	glViewport(0, 0, prevViewport[2], prevViewport[3]);

		
	// Print information
	std::cout << "OpenGL context" << std::endl;
	std::cout << "   version  . . : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "   vendor . . . : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "   renderer . . : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "   GLSL . . . . : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Success!!
	return true;
}


void LIB_API Engine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	ShaderWrapper::shader->setVec3(ShaderWrapper::shader->getParamLocation("fog"), glm::vec3(r, g, b));
}


void LIB_API Engine::enableWireframe() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void LIB_API Engine::disableWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LIB_API Engine::enableGouraund() {
	glShadeModel(GL_SMOOTH);
}

void LIB_API Engine::disableGouraund() {
	glShadeModel(GL_FLAT);
}

/**
* Swap back-buffer and front-buffer to show current render result
*/
void LIB_API Engine::swapBuffers() {
	// Swap back buffer <-> front buffer
	//glutSwapBuffers();
}

bool LIB_API Engine::free()
{
	// Really necessary?
	if (!m_initFlag)
	{
		std::cout << "ERROR: class not initialized" << std::endl;
		return false;
	}

	// Delete shaders
	delete fs;
	delete vs;

	// Done:
	m_initFlag = false;
	return true;
}

void LIB_API Engine::render3D(PerspectiveCamera* camera) {
	// Save camera
	m_curr_3Dcamera = camera;

	// Set the far plane used for creating the fog effect
	ShaderWrapper::shader->setFloat(ShaderWrapper::shader->getParamLocation("farPlane"), camera->getFar());

	// Store the current viewport size:
	GLint prevViewport[4];
	glGetIntegerv(GL_VIEWPORT, prevViewport); // <---- ERROR!

	// Render to each eye:   
	for (int c = 0; c < EYE_LAST; c++)
	{
		// Render into this FBO:
		fbo[c]->render();

		// Clear the FBO content:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		////////////////
		// 3D rendering:

		glm::mat4 cameraMat = glm::translate(camera->getMatrix(), glm::vec3(-10.0f * c, 0.0f, 0.0f));

		// Setup params for the PPL shader:
		ShaderWrapper::shader->render();
		m_curr_3Dcamera->render(m_curr_3Dcamera->getProperties());

		// Activate lighting
		//glEnable(GL_LIGHTING);

		// Start rendering the scene
		if (m_scene_graph != nullptr) {
			// Clear rendering list
			m_rendering_list->clear();

			// Popolate rendering list: the second parameter is an idetity matrix because the "pass" function is recursive and
			// need the matrix of the parent node when rendering its child. Since "root" has no parent, pass an identity matrix instead
			m_rendering_list->pass(m_scene_graph, glm::mat4(1));

			// Render
			m_rendering_list->render(cameraMat);
		}
		else {
			std::cout << "[ENGINE] WARNING: Scene graph not initialized" << std::endl;
			return;
		}
	}

	// Done with the FBO, go back to rendering into the window context buffers:
	Fbo::disable();
	glViewport(0, 0, prevViewport[2], prevViewport[3]);

	////////////////
	// 2D rendering:
	m_curr_2Dcamera = new OrthographicCamera{ "2d Camera", glm::mat4(1), APP_WINDOWSIZEX, APP_WINDOWSIZEY };

	// Set a matrix for the left "eye":    
	glm::mat4 f = glm::mat4(1.0f);

	// Setup the passthrough shader:
	ShaderWrapper::passthroughShader->render();
	ShaderWrapper::passthroughShader->setMatrix(ShaderWrapper::passthroughShader->getParamLocation("projection"), m_curr_2Dcamera->getProperties());
	ShaderWrapper::passthroughShader->setMatrix(ShaderWrapper::passthroughShader->getParamLocation("modelview"), f);
	ShaderWrapper::passthroughShader->setVec4(ShaderWrapper::passthroughShader->getParamLocation("color"), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	m_quad->render(fboTexId[EYE_LEFT]);

	// Do the same for the right "eye": 
	f = glm::translate(glm::mat4(1.0f), glm::vec3(APP_WINDOWSIZEX / 2, 0.0f, 0.0f));
	ShaderWrapper::passthroughShader->setMatrix(ShaderWrapper::passthroughShader->getParamLocation("modelview"), f);
	ShaderWrapper::passthroughShader->setVec4(ShaderWrapper::passthroughShader->getParamLocation("color"), glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
	
	m_quad->render(fboTexId[EYE_RIGHT]);

	// Swap buffers:
	glutSwapBuffers();

	// force refresh
	glutPostWindowRedisplay(m_windowId);
}


void LIB_API Engine::render2D(OrthographicCamera* camera, const std::list<std::tuple<std::string, int>>& list) {

	// Save camera
	m_curr_2Dcamera = camera;

	// Disable lighting
	//glDisable(GL_LIGHTING);

	// Set properties
	m_curr_2Dcamera->render(m_curr_2Dcamera->getProperties());

	//glColor3f(0.4f, 0.4f, 0.4f);

	for (const auto& element : list) {
		//glRasterPos2f(10.0f, static_cast<float>(std::get<1>(element)));
		//glutBitmapString(GLUT_BITMAP_8_BY_13, reinterpret_cast<const unsigned char*>(std::get<0>(element).c_str()));
	}

	// force refresh
	glutPostRedisplay();
}

void LIB_API Engine::run(void (*renderFunction)()) {
	glutDisplayFunc(renderFunction);
	glutMainLoop();

	// Stopped running, set m_isRunning to false
	m_isRunning = false;
}


//
// Callback setters
//

void LIB_API Engine::setSpecialKeyboardFunction(void (*callback)(int,int,int))
{
	glutSpecialFunc(callback);
}

void LIB_API Engine::setKeyboardFunction(void (*callback)(unsigned char,int,int)) {
	glutKeyboardFunc(callback);
}

void LIB_API Engine::setMouseFunction(void (*callback)(int, int, int, int)) {
	glutMouseFunc(callback);
}

void LIB_API Engine::setMouseWheelFunction(void (*callback)(int, int, int, int)) {
	glutMouseWheelFunc(callback);
}

void LIB_API Engine::setMouseMotionFunction(void (*callback)(int, int)) {
	glutPassiveMotionFunc(callback);
}


void LIB_API Engine::setTimerFunction(void (*callback)(int)) {
	userTimerCallback = callback;
	glutTimerFunc(1000, timerCallback, 0);
}


bool LIB_API Engine::isRunning() {
	return m_isRunning;
}

// Load scene graph given a .ovo file
void LIB_API Engine::load(const std::string& path, const std::string& texturesDir) {
	Ovoreader ovoreader;
	m_scene_graph = ovoreader.readFile(path.c_str(), texturesDir.c_str());
}

// Load scene graph given a pointer to node
void LIB_API Engine::load(Node* root) {
	m_scene_graph = root;
}

void LIB_API Engine::setGraphics(EngineGraphics& g) {
	// Save new configuration
	m_graphics_settings = &g;

	// Apply settings
	Texture::setFilter(g.filter, g.mipmap);
	Texture::setTextureWrap(g.wrap);

	// If anisotropicFiltering is enabled
	if (g.useAnisotropicFiltering) {
		try {
			Texture::enableAnisotropicFiltering(g.anisotropicFilteringValue);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "WARNING: Error while enabling anisotropic filtering. " << ex.what() << std::endl;

			// Disable anisotropic filtering
			Texture::disableAnisotropicFiltering();
		}
	}
	else {
		Texture::disableAnisotropicFiltering();
	}
}

Node LIB_API* Engine::getNode(const std::string& name)
{
	//if the scene is not setted return null
	if (m_scene_graph == nullptr) {
		return nullptr;
	}

	//convert std::string to a const char pointer to avoid copy
	const char* searchName = name.c_str();
	return m_scene_graph->searchNode(searchName);
}

unsigned int LIB_API Engine::getWindowWidth() {
	return m_window_height;
}

unsigned int LIB_API Engine::getWindowHeight() {
	return m_window_width;
}

void LIB_API Engine::redisplay() {
	if (Engine::isRunning()) {
		glutPostRedisplay();
	}
	else {
		cout << "[ENGINE] Warning: The engine should be initialized before calling redisplay function" << endl;
	}
}
