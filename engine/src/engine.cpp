//////////////
// #INCLUDE //
//////////////

#include <iostream>
#include <fstream>
#include <cstring>

	// Project classes
#include "engine.h"
#include "perspectiveCamera.h"
#include "shader.h"
#include "shaderManager.h"

	// C/C++
#include <iostream>
#include <thread>

	// Shaders:
#include "shader.vertex.cpp"
#include "shader.fragmentOmniDirectionalLight.cpp"
#include "shader.fragmentDirectionalLight.cpp"
#include "shader.fragmentSpotLight.cpp"
#include "shader.passthroughVertex.cpp"
#include "shader.passthroughFragment.cpp"
#include "shader.skyboxPassthroughVertex.cpp"
#include "shader.skyboxPassthroughFragment.cpp"
#include "shader.leapVertex.cpp"
#include "shader.leapFragment.cpp"

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


////////////
// STATIC //
////////////

// Reserved pointer:
Node* Engine::m_scene_graph = nullptr;
RenderingList* Engine::m_rendering_list = new RenderingList{ "Rendering list" };
bool Engine::m_initFlag = false;
bool Engine::m_isRunning = false;
int Engine::m_window_height = -1;
int Engine::m_window_width = -1;
int Engine::m_windowId = -1;
float Engine::m_playerHeight = 0.0f;
glm::vec3 Engine::m_background_color;
PerspectiveCamera* Engine::m_curr_3Dcamera = nullptr;
OrthographicCamera* Engine::m_curr_2Dcamera = new OrthographicCamera{ "2d Camera", glm::mat4(1), APP_WINDOWSIZEX, APP_WINDOWSIZEY };
EngineGraphics* Engine::m_graphics_settings = nullptr;
Quad* Engine::m_quad = nullptr;
std::string Engine::m_renderType = "";
OvVR* Engine::m_ovr = nullptr;
Skybox* Engine::m_skybox = nullptr;
Leap* Engine::m_leap = nullptr;

// Enums:
enum Eye
{
	EYE_LEFT = 0,
	EYE_RIGHT = 1,

	// Terminator:
	EYE_LAST,
};
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
	if (id != 131185 && type != 33361)
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

	if (m_renderType == "Stereoscopic") {
		for (int c = 0; c < EYE_LAST; c++)
		{
			glDeleteTextures(1, &fboTexId[c]);
			delete fbo[c];
		}
	}
	FreeImage_DeInitialise();
}

void Engine::reshapeCallback(int width, int height) {
	if (m_renderType == "Stereoscopic"){
		// ... ignore the params, we want a fixed-size window
		// (bad) trick to avoid window resizing:
		if (width != APP_WINDOWSIZEX || height != APP_WINDOWSIZEY)
			glutReshapeWindow(APP_WINDOWSIZEX, APP_WINDOWSIZEY);
	}
	else {
		// Update viewport size:
		glViewport(0, 0, width, height);

		// Width + Height fields
		m_window_width = width;
		m_window_height = height;

		// If current 3D camera is set, update width / height
		if (m_curr_3Dcamera != nullptr) {
			m_curr_3Dcamera->updateWindowSize(width, height);
			std::cout << "[3D] -> " << width << "x" << height << std::endl;
		}

		// Update viewport size:
		glViewport(0, 0, width, height);

	}


}

void LIB_API Engine::timerCallback(int value) {
	(*userTimerCallback)(value);
	glutTimerFunc(1000, timerCallback, 0);
}


void Engine::buildShaders() {
	// Per pixel lighting shaders
	// Vertex shader
	Shader* vs = ShaderManager::createShader("vertexShader");
	vs->loadFromMemory(Shader::TYPE_VERTEX, vertShader);

	// Compile fragment shader:
	Shader* fsOmni = ShaderManager::createShader("fragmentShaderOmnidirectional");
	fsOmni->loadFromMemory(Shader::TYPE_FRAGMENT, fragShaderOmniDirectionalLight);

	// Program1: Omnidirectional light
	Shader* progShader = ShaderManager::createShader("programShaderOmnidirectionalLight");
	progShader->build(vs, fsOmni);
	progShader->render();
	progShader->bind(0, "in_Position");
	progShader->bind(1, "in_Normal");
	progShader->bind(2, "in_TexCoord");

	// Program2: Directional light
	Shader* fsDir = ShaderManager::createShader("fragmentShaderDirectional");
	fsDir->loadFromMemory(Shader::TYPE_FRAGMENT, fragShaderDirectionalLight);
	Shader* progShader2 = ShaderManager::createShader("programShaderDirectionalLight");
	progShader2->build(vs, fsDir);
	progShader2->render();
	progShader2->bind(0, "in_Position");
	progShader2->bind(1, "in_Normal");
	progShader2->bind(2, "in_TexCoord");

	// Program3: Spot light
	Shader* fsSpot = ShaderManager::createShader("fragmentShaderSpot");
	fsSpot->loadFromMemory(Shader::TYPE_FRAGMENT, fragShaderSpotLight);
	Shader* progShader3 = ShaderManager::createShader("programShaderSpotLight");
	progShader3->build(vs, fsSpot);
	progShader3->render();
	progShader3->bind(0, "in_Position");
	progShader3->bind(1, "in_Normal");
	progShader3->bind(2, "in_TexCoord");

	// Passthrough shader:
	Shader* pvs = ShaderManager::createShader("Passthrough Vertex Shader");
	pvs->loadFromMemory(Shader::TYPE_VERTEX, passthroughVertShader);
	Shader* pfs = ShaderManager::createShader("Passthrough Fragment Shader");
	pfs->loadFromMemory(Shader::TYPE_FRAGMENT, passthroughFragShader);
	// Setup per pixel lighting shader program:
	Shader* passthroughShader = ShaderManager::createShader("Passthrough Program Shader");
	passthroughShader->build(pvs, pfs);
	passthroughShader->render();
	passthroughShader->bind(0, "in_Position");
	passthroughShader->bind(2, "in_TexCoord");

	// Skybox passthrough shader:
	Shader* spvs = ShaderManager::createShader("Skybox Passthrough Vertex Shader");
	spvs->loadFromMemory(Shader::TYPE_VERTEX, skyboxPassthroughVertShader);
	Shader* spfs = ShaderManager::createShader("Skybox Passthrough Fragment Shader");
	spfs->loadFromMemory(Shader::TYPE_FRAGMENT, skyboxPassthroughFragShader);
	Shader* skyboxPassthroughShader = ShaderManager::createShader("Skybox Passthrough Program Shader");
	skyboxPassthroughShader->build(spvs, spfs);
	skyboxPassthroughShader->render();
	skyboxPassthroughShader->bind(0, "in_Position");

	// Leap shader:
	Shader* lvs = ShaderManager::createShader("Leap Vertex Shader");
	lvs->loadFromMemory(Shader::TYPE_VERTEX, leapVertShader);
	Shader* lfs = ShaderManager::createShader("Leap Fragment Shader");
	lfs->loadFromMemory(Shader::TYPE_FRAGMENT, leapFragShader);
	Shader* leapShader = ShaderManager::createShader("Leap Program Shader");
	leapShader->build(lvs, lfs);
	leapShader->render();
	leapShader->bind(0, "in_Position");

	// Set default shader
	ShaderManager::setActiveShader("programShaderSpotLight");
}

////////////
// PUBLIC //
////////////

bool LIB_API Engine::init(const char* title, unsigned int width, unsigned int height, int* argc, char** argv, std::string renderingType)
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

	// Copy config file
	m_renderType = renderingType;

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

	if (m_renderType == "Stereoscopic") {
		m_window_width = APP_WINDOWSIZEX;
		m_window_height = APP_WINDOWSIZEY;
		glutInitWindowSize(APP_WINDOWSIZEX, APP_WINDOWSIZEY);
	}
	else {
		m_window_width = width;
		m_window_height = height;
		glutInitWindowSize(width, height);
	}

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
	glEnable(GL_CULL_FACE);

	// Set reshape function
	glutReshapeFunc(reshapeCallback);

	// Init FreeImage for texture mapping
	FreeImage_Initialise();

	// Ovr init
	if (m_renderType == "Stereoscopic")
	{
		m_ovr = new OvVR();
		if (m_ovr->init() == false)
		{
			std::cout << "[ERROR] Unable to init OpenVR" << std::endl;
			delete m_ovr;
			return 1;
		}

		// Report some info:
		std::cout << "   Manufacturer . . :  " << m_ovr->getManufacturerName() << std::endl;
		std::cout << "   Tracking system  :  " << m_ovr->getTrackingSysName() << std::endl;
		std::cout << "   Model number . . :  " << m_ovr->getModelNumber() << std::endl;
	}


	// Set running state
	m_isRunning = true;

	// Build shaders
	buildShaders();

	if (m_renderType == "Stereoscopic") {

		// Create quad
		m_quad = new Quad("Quad", m_window_width, m_window_height);

		// Load FBO and its texture:
		GLint prevViewport[4];
		glGetIntegerv(GL_VIEWPORT, prevViewport);

		for (int c = 0; c < EYE_LAST; c++)
		{
			glGenTextures(1, &fboTexId[c]);
			glBindTexture(GL_TEXTURE_2D, fboTexId[c]);
			if (m_renderType == "Stereoscopic") {
				int fboSizeX = m_ovr->getHmdIdealHorizRes();
				int fboSizeY = m_ovr->getHmdIdealVertRes();
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fboSizeX, fboSizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); // GL_RGBA8 is IMPORTANT!!
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, APP_FBOSIZEX, APP_FBOSIZEY, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			fbo[c] = new Fbo("FBO" + c);
			fbo[c]->bindTexture(0, Fbo::BIND_COLORTEXTURE, fboTexId[c]);
			if (m_renderType == "Stereoscopic") {
				int fboSizeX = m_ovr->getHmdIdealHorizRes();
				int fboSizeY = m_ovr->getHmdIdealVertRes();
				fbo[c]->bindRenderBuffer(1, Fbo::BIND_DEPTHBUFFER, fboSizeX, fboSizeY);
			}
			else {
				fbo[c]->bindRenderBuffer(1, Fbo::BIND_DEPTHBUFFER, APP_FBOSIZEX, APP_FBOSIZEY);
			}
			if (!fbo[c]->isOk())
				std::cout << "[ERROR] Invalid FBO" << std::endl;
		}
		// Dummy declaration
		unsigned int ftt;
		glGenTextures(1, &ftt);
		glBindTexture(GL_TEXTURE_2D, ftt);

		Fbo::disable();
		glViewport(0, 0, prevViewport[2], prevViewport[3]);
	}

	// Leap motion
	m_leap = new Leap("Leapmotion", glm::mat4(1.0f));
	if (!m_leap->init())
	{
		std::cout << "[ERROR] Unable to init Leap Motion" << std::endl;
		delete m_leap;
		return false;
	}
	m_leap->buildHands();

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
	m_background_color = glm::vec3(r, g, b);
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
	ShaderManager::free();

	// Delete ovr
	if (m_renderType == "Stereoscopic")
		delete m_ovr;

	// Delete leap
	m_leap->free();

	// Done:
	m_initFlag = false;
	return true;
}

void LIB_API Engine::render(PerspectiveCamera* camera) {
	// Save camera
	m_curr_3Dcamera = camera;

	if (m_renderType == "Stereoscopic") {
		stereoscopicRender();
	}
	else {
		// Start rendering
		if (m_scene_graph != nullptr) {
			// Clear rendering list
			m_rendering_list->clear();
			// Popolate rendering list: the second parameter is an idetity matrix because the "pass" function is recursive and
			// need the matrix of the parent node when rendering its child. Since "root" has no parent, pass an identity matrix instead
			m_rendering_list->pass(m_scene_graph, glm::mat4(1));
			// Render
			m_rendering_list->m_camera = m_curr_3Dcamera;
			m_rendering_list->render(m_curr_3Dcamera->getMatrix());

			ShaderManager::setActiveShader("Skybox Passthrough Program Shader");
			Shader* progShader = ShaderManager::getActiveShader();
			progShader->setMatrix(progShader->getParamLocation("projection"), m_curr_3Dcamera->getProperties());
			m_skybox->render(glm::scale(glm::inverse(m_curr_3Dcamera->getMatrix()), glm::vec3(100.0f, 100.0f, 100.0f)));
		}
		else {
			std::cout << "[ENGINE] WARNING: Scene graph not initialized" << std::endl;
			return;
		}
	}

	// Swap buffers:
	glutSwapBuffers();

	// force refresh
	glutPostWindowRedisplay(m_windowId);
}

void LIB_API Engine::stereoscopicRender() {
	// Store the current viewport size:
	GLint prevViewport[4];
	glGetIntegerv(GL_VIEWPORT, prevViewport);

	// Update user position:
	m_ovr->update();
	glm::mat4 headPos = m_ovr->getModelviewMatrix();
	
	 // Update camera position mantaining xyz position and using the head rotation
	glm::mat4 realPos = headPos;
	
	// Get the real position of the camera taking in consideration camera and head position
	glm::mat4 currentCameraPos = m_curr_3Dcamera->getMatrix();
	realPos = currentCameraPos * headPos;

	// translate realPos down by the height of the player
	realPos[3][1] -= m_playerHeight;
	

	for (int c = 0; c < m_ovr->EYE_LAST; c++) {
		// Get OpenVR matrices:
		OvVR::OvEye curEye = (OvVR::OvEye)c;
		glm::mat4 projMat = m_ovr->getProjMatrix(curEye, m_curr_3Dcamera->getNear(), m_curr_3Dcamera->getFar());
		glm::mat4 eye2Head = m_ovr->getEye2HeadMatrix(curEye);

		// Update camera projection matrix
		m_curr_3Dcamera->setPropertiesMatrix(projMat * glm::inverse(eye2Head));


		// Render into this FBO:
		fbo[c]->render();

		// Clear the FBO content:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Start rendering the scene
		if (m_scene_graph != nullptr) {
			// Clear rendering list
			m_rendering_list->clear();
			// Popolate rendering list: the second parameter is an idetity matrix because the "pass" function is recursive and
			// need the matrix of the parent node when rendering its child. Since "root" has no parent, pass an identity matrix instead
			m_rendering_list->pass(m_scene_graph, glm::mat4(1));
			// Render
			m_rendering_list->m_camera = m_curr_3Dcamera;
			m_rendering_list->m_skybox = m_skybox;
			m_rendering_list->render(realPos);

			ShaderManager::setActiveShader("Skybox Passthrough Program Shader");
			Shader* progShader = ShaderManager::getActiveShader();
			progShader->setMatrix(progShader->getParamLocation("projection"), m_curr_3Dcamera->getProperties());

			m_skybox->render(glm::scale(glm::inverse(realPos), glm::vec3(100.0f, 100.0f, 100.0f)));

			ShaderManager::setActiveShader("Leap Program Shader");
			progShader = ShaderManager::getActiveShader();
			progShader->setMatrix(progShader->getParamLocation("projection"), m_curr_3Dcamera->getProperties());
			m_leap->render(realPos);
		}
		else {
			std::cout << "[ENGINE] WARNING: Scene graph not initialized" << std::endl;
			return;
		}

		m_ovr->pass(curEye, fboTexId[c]);
	}
	m_ovr->render();

	// Done with the FBO, go back to rendering into the window context buffers:
	Fbo::disable();
	glViewport(0, 0, prevViewport[2], prevViewport[3]);

	// Set a matrix for the left "eye":    
	glm::mat4 f = glm::mat4(1.0f);
	// Setup the passthrough shader:
	ShaderManager::setActiveShader("Passthrough Program Shader");
	Shader* passthroughShader = ShaderManager::getActiveShader();

	passthroughShader->setMatrix(passthroughShader->getParamLocation("projection"), m_curr_2Dcamera->getProperties());
	passthroughShader->setMatrix(passthroughShader->getParamLocation("modelview"), f);
	passthroughShader->setVec4(passthroughShader->getParamLocation("color"), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	m_quad->render(fboTexId[EYE_LEFT]);
	// Do the same for the right "eye": 
	f = glm::translate(glm::mat4(1.0f), glm::vec3(APP_WINDOWSIZEX / 2, 0.0f, 0.0f));
	passthroughShader->setMatrix(passthroughShader->getParamLocation("modelview"), f);
	passthroughShader->setVec4(passthroughShader->getParamLocation("color"), glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
	m_quad->render(fboTexId[EYE_RIGHT]);
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

void LIB_API Engine::setSpecialKeyboardFunction(void (*callback)(int, int, int))
{
	glutSpecialFunc(callback);
}

void LIB_API Engine::setKeyboardFunction(void (*callback)(unsigned char, int, int)) {
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

void LIB_API Engine::setCollisionCallback(void(*callback)(void*)) {
	m_leap->setCollisionCallback(callback);
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

void LIB_API Engine::loadSkybox(const std::string& filepath, const std::string* cubemapNames) {
	m_skybox = new Skybox("Skybox", filepath, cubemapNames);
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

void LIB_API Engine::setPlayerHeight(float height) {
	m_playerHeight = height;
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


void LIB_API Engine::redisplay() {
	if (Engine::isRunning()) {
		glutPostRedisplay();
	}
	else {
		cout << "[ENGINE] Warning: The engine should be initialized before calling redisplay function" << endl;
	}
}
