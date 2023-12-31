#pragma once

/**
 * \file         engine.h
 * \brief        An OpenGL-based graphic engine .dll/.so dynamic library
 */

 /////////////
 // CLASSES //
 /////////////
#include "camera.h"
#include "orthographicCamera.h"
#include "perspectiveCamera.h"
#include "lib.h"
#include "renderingList.h"
#include "ovoreader.h"
#include "texture.h"
#include "shader.h"
#include "fbo.h"
#include "quad.h"
#include "skybox.h"
#include "leapMotion.h"

#include <queue>
#include "ovr.h"

/**
 * \struct EngineGraphics
 * \brief Struct containing graphics settings for the engine.
 */
struct LIB_API EngineGraphics {
	/**
	 * \var filter
	 * The texture filter to use when rendering textures.
	 */
	Filter filter;
	/**
	 * \var wrap
	 * The texture wrap mode to use when rendering textures.
	 */
	TextureWrap wrap;
	/**
	 * \var mipmap
	 * The texture mipmap to use when rendering textures.
	 */
	TextureMipmap mipmap;
	/**
	 * \var useAnisotropicFiltering
	 * Flag indicating whether to use anisotropic filtering when rendering textures.
	 */
	bool useAnisotropicFiltering;
	/**
	 * \var anisotropicFilteringValue
	 * The level of anisotropic filtering to use when rendering textures.
	 */
	unsigned int anisotropicFilteringValue;
};

/**
 * \brief The main class of the graphic engine.
 *
 * This class contains the main functions for initializing and running the engine,
 * as well as functions for loading and rendering 3D models and setting the camera.
 */
class LIB_API Engine {

private:
	/**
	 * Private constructor to prevent instantiation of the class.
	 */
	Engine();

	/**
	 * Private destructor to prevent deletion of the class.
	 */
	~Engine();

	/**
	 * The root node of the scene graph.
	 */
	static Node* m_scene_graph;

	/**
	 * The rendering list used to draw the 3D models.
	 */
	static RenderingList* m_rendering_list;

	/**
	 * Flag indicating whether the engine has been initialized.
	 */
	static bool m_initFlag;

	/**
	 * Flag indicating whether the engine is running.
	 */
	static bool m_isRunning;

	/**
	 * The ID of the window.
	 */
	static int m_windowId;

	/**
	* The width of the window.
	*/
	static int m_window_width;
	/**
	 * The height of the window.
	 */
	static int m_window_height;

	/**
	 * The current camera being used by the engine.
	 */
	static PerspectiveCamera* m_curr_3Dcamera;

	/**
	* The current 2D camera being used by the engine.
	*/
	static OrthographicCamera* m_curr_2Dcamera;

	/**
	* Graphics settings
	*/
	static EngineGraphics* m_graphics_settings;


	/**
	* Static Quad used for 2D rendering
	*/
	static Quad* m_quad;

	/**
	* Static Skybox
	*/
	static Skybox* m_skybox;

	/**
	* Background color
	*/
	static glm::vec3 m_background_color;

	/**
	 * Rendering type
	 */
	static std::string m_renderType;

	/**
	* OVR
	*/
	static OvVR* m_ovr;

	/*
	* Leap
	*/
	static Leap* m_leap;

	/** 
	* Player Height.
	*/
	static float m_playerHeight;

	/**
	 * Callback function for reshaping the window.
	 *
	 * \param width The new window width.
	 * \param height The new window height.
	 */
	static void reshapeCallback(int width, int height);

	/**
	* Callback function for timer the window.
	*
	* @param value passepartout value
	*/
	static void timerCallback(int value);

	/**
	* \brief Initialize and build program shaders
	*/
	static void buildShaders();

public:

	/**
	 * Initialize the engine.
	 *
	 * \param title The title of the window.
	 * \param argc Pointer to the number of command-line arguments.
	 * \param argv Array of command-line arguments.
	 * \return True if the initialization was successful, false otherwise.
	 */
	static bool init(const char* title, unsigned int width, unsigned int height, int* argc, char** argv, std::string renderingType);

	/**
	 * Load a 3D model from a file.
	 *
	 * \param filepath The path to the file containing the 3D model.
	 * \param texturesDir The path to the directory containing the texture resources.
	 */
	static void load(const std::string& filepath, const std::string& texturesDir);

	/**
	* Load a 3D model from a scene graph.
	*
	* \param root The root node of the model's scene graph.
	*/
	static void load(Node* root);

	/**
	 * Load a 3D model from a file.
	 *
	 * \param filepath The path to the file containing the texture composing the skybox.
	 * \param filepath An array containing the names of the 6 textures composing the skybox.
	 */
	static void loadSkybox(const std::string& filepath, const std::string* cubemapNames);

	/**
	 * Clear the scene.
	 */
	static void clear();

	/**
	 * Set the background color of the window.
	 *
	 * \param r The red component of the background color (range: 0.0 to 1.0).
	 * \param g The green component of the background color (range: 0.0 to 1.0).
	 * \param b The blue component of the background color (range: 0.0 to 1.0).
	 */
	static void setBackgroundColor(float r, float g, float b);

	/** 
	 * Set playerHeight
	 */
	static void setPlayerHeight(float height);

	/**
	 * Swap the front and back buffers.
	 */
	static void swapBuffers();

	/**
	 * Free the resources used by the engine.
	 *
	 * \return True if the resources were successfully freed, false otherwise.
	 */
	static bool free();

	/**
	 * Render the scene.
	 * 
	 * \param camera with which render the scene.
	 */
	static void render(PerspectiveCamera* camera);

	/**
	 * Render the scene using FBOs.
	 *
	 */
	static void stereoscopicRender();

	/**
	 * Run the engine loop.
	 *
	 * \param updateFunction The function to call for updating the scene.
	 */
	static void run(void (*updateFunction)());

	/**
	 * Enable wireframe rendering.
	 */
	static void enableWireframe();

	/**
	* Disable wireframe rendering.
	*/
	static void disableWireframe();

	/**
	 * Enable Gouraund shading.
	 */
	static void enableGouraund();

	/**
	* Disable Gouraund shading.
	*/
	static void disableGouraund();
	/**
	 * Set the keyboard callback function.
	 *
	 * \param callback The callback function to set.
	 */
	static void setKeyboardFunction(void (*callback)(unsigned char, int, int));

	/**
	 * Set the special keyboard callback function.
	 *
	 * \param callback The callback function to set.
	 */
	static void setSpecialKeyboardFunction(void (*callback)(int, int, int));

	/**
	* Set the timer callback function.
	*
	* \param callback The callback function to set.
	*/
	static void setTimerFunction(void (*callback)(int));

	/**
	 * \brief Set collision callback
	 */
	static void setCollisionCallback(void(*callback)(void*));

	/**
	 * Check if the engine is running.
	 *
	 * \return True if the engine is running, false otherwise.
	 */
	static bool isRunning();

	/**
	* Set new graphics settings profile
	* 
	* @param g EngineGraphics instance containing the actual graphic profile
	*/
	static void setGraphics(EngineGraphics& g);

	/**
	* Search and return the first node found in the scene
	*
	* @param name Name of the node
	*/
	static Node* getNode(const std::string& name);


	/**
	 * Force rendering.
	 */
	static void redisplay();

	/**
	 * Set mouse callback function.
	 * 
	 * \param callback Callback function pointer
	 */
	static void setMouseFunction(void (*callback)(int, int, int, int));

	/**
	 * Set mouse wheel callback function.
	 * 
	 * \param callback Callback function pointer
	 */
	static void setMouseWheelFunction(void (*callback)(int, int, int, int));

	/**
	 * Set mouse motion callback function. This event is fired every time the mouse moves on the screen.
	 *
	 * \param callback Callback function pointer
	 */
	static void setMouseMotionFunction(void (*callback)(int, int));
};

