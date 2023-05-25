#include "main.h"

// Special key definition
#define KEY_LEFT					0x0064
#define KEY_UP						0x0065
#define KEY_RIGHT					0x0066
#define KEY_DOWN					0x0067
#define KEY_SHIFT_L					0x0070
#define KEY_CTRL_L					0x0072

// Create camera
glm::mat4 startCameraCoordinateStandard = glm::translate(glm::mat4(1.f), glm::vec3(15.f, 15.f, 50.f));
unsigned int width = 512;
unsigned int height = 512;
float near = 0.01f;
float far = 250.f;
float fov = 90.f;
PerspectiveCamera* camera3D;
PerspectiveCamera* camera3DHook;
PerspectiveCamera* camera3DCabine;

// Current camera
CameraNode* currentCamera;

// Dynamic camera parameters
float cameraSpeed = 0.5f;
float camera_sensitivity = 1.0f;

// SceneObject objects
Node* root;
Node* crane;
Node* slewingUnit;
Node* trolley;
Node* cable1;
Node* cable2;
Node* hook;
Node* container1;
Node* container2;
const float heightContainer = 3.538f;
Node* plane;
Node* cabine;
Node* cameraVRPlaceholder;

// Rendering type
std::string renderingType;

// Settings
float craneRotationSpeed = 1.f;
float cablesScaleSpeed = 0.05f;
float trolleySpeed = 0.5f;
float thresholdHook = 10.f;

// flags
bool hooked = false;
Node* hookedNode = nullptr;
float extensionsCableCount = 0;
float movementTrolleyCount = 0;

// settings flags
bool isWireframe = false;
bool isGouraund = true;
bool timerFlag = true;

// Range of movement
const float minTrolley = -50;
const float maxTrolley = 6;
const float maxExtensionsCable = 47.5;

// FPS
int fps = 0;
int frames = 0;

// Command map
std::map<Mesh*, void(*)()> commands;
Mesh* hookButton = nullptr;

void display() {
	// Clear image
	Engine::clear();

	// Render scene
	Engine::render(currentCamera->getCamera());

	// Increment frame
	frames++;

	Engine::swapBuffers();
}

void moveCableUp() {
	if (extensionsCableCount > 0) {
		// There is an object between the hook and the cable
		Node* hookParent = cable1->getChildren().at(0);

		cable1->setMatrix(glm::scale(cable1->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));
		cable2->setMatrix(glm::scale(cable2->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));

		// adapt matrix
		hookParent->setMatrix(glm::scale(hookParent->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));

		extensionsCableCount--;
	}
}

void moveCableDown() {
	if (maxExtensionsCable > extensionsCableCount + 1) {
		// There is an object between the hook and the cable
		Node* hookParent = cable1->getChildren().at(0);

		cable1->setMatrix(glm::scale(cable1->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));
		cable2->setMatrix(glm::scale(cable2->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));

		// adapt matrix
		hookParent->setMatrix(glm::scale(hookParent->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));

		extensionsCableCount++;
	}
}

void rotateCounterclockwise() {
	slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
}

void rotateClockwise() {
	slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(-craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
}

void moveTrolleyForward() {
	if (maxTrolley > movementTrolleyCount + 1) {
		trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(trolleySpeed, 0.0f, 0.0f)));

		movementTrolleyCount++;
	}
}

void moveTrolleyBackward() {
	if (minTrolley < movementTrolleyCount - 1) {
		trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(-trolleySpeed, 0.0f, 0.0f)));

		movementTrolleyCount--;
	}
}

void hookContainer() {
	// If function has been called recently, ignore the call
	if (!timerFlag)
		return;

	timerFlag = false;
	if (!hooked) {
		// hook one of the containers

		// Get world coordinates
		glm::vec3 worldCordhook{ hook->getWorldCoordinateMatrix()[3] };
		glm::vec3 worldCordContainer1{ container1->getWorldCoordinateMatrix()[3] };
		glm::vec3 worldCordContainer2{ container2->getWorldCoordinateMatrix()[3] };

		// Calculate distance
		float distanceHookContainer1 = glm::distance(worldCordhook, worldCordContainer1);
		float distanceHookContainer2 = glm::distance(worldCordhook, worldCordContainer2);

		// Hook the object if is it near
		if (distanceHookContainer1 < thresholdHook) {
			// Calculate matrix of the container hooked
			glm::mat4 matrixContainer1 = glm::inverse(hook->getWorldCoordinateMatrix()) * container1->getWorldCoordinateMatrix();
			// Reset world coordinates
			matrixContainer1[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);
			// Change the scene
			container1->getParent()->removeChild(container1);
			container1->setParent(hook);
			container1->setMatrix(matrixContainer1);
			// Set hooked as true
			hooked = !hooked;
			hookedNode = container1;
		}
		else if (distanceHookContainer2 < thresholdHook) {
			// Calculate matrix of the container hooked
			glm::mat4 matrixContainer2 = glm::inverse(hook->getWorldCoordinateMatrix()) * container2->getWorldCoordinateMatrix();
			// Reset world coordinates
			matrixContainer2[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);
			// Change the scene
			container2->getParent()->removeChild(container2);
			container2->setParent(hook);
			container2->setMatrix(matrixContainer2);
			// Set hooked as true
			hooked = !hooked;
			hookedNode = container2;
		}
	}
	else {
		// Get world coordinates
		glm::vec3 worldObjHooked{ hookedNode->getWorldCoordinateMatrix()[3] };
		glm::vec3 worldCordPlane{ plane->getWorldCoordinateMatrix()[3] };
		// Calculate distance
		float distanceObjPlane = worldObjHooked.y - worldCordPlane.y - heightContainer;

		if (distanceObjPlane < abs(thresholdHook)) {
			// World coordinates hooked obj
			glm::mat4 worldCoordHooked = hookedNode->getWorldCoordinateMatrix();
			worldCoordHooked[3].y = heightContainer;
			// Change the scene
			hookedNode->getParent()->removeChild(hookedNode);
			hookedNode->setParent(root);
			hookedNode->setMatrix(worldCoordHooked);
			// Set hooked as true
			hooked = !hooked;
			hookedNode = nullptr;
		}
	}
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == '1') {
		if (isWireframe) {
			cout << "[CRANE] Settings: Disable wireframe" << endl;
			Engine::disableWireframe();
		}
		else {
			cout << "[CRANE] Settings: Enable wireframe" << endl;
			Engine::enableWireframe();
		}
		isWireframe = !isWireframe;
	}
	else if (key == '2') {
		if (isGouraund) {
			cout << "[CRANE] Settings: Gouraund shading disabled" << endl;
			Engine::disableGouraund();
		}
		else {
			cout << "[CRANE] Settings: Gouraund shading enabled" << endl;
			Engine::enableGouraund();
		}
		isGouraund = !isGouraund;
	}
	else if (key == 'c') {
		if (currentCamera->getNext() != nullptr) {
			currentCamera->getNext()->getCamera()->updateWindowSize(currentCamera->getCamera()->getWidth(), currentCamera->getCamera()->getHeight());
			currentCamera = currentCamera->getNext();
		}
	}

	else if (key == 'g') {
		rotateCounterclockwise();
	}
	else if (key == 'l') {
		rotateClockwise();
	}
	else if (key == 'h') {
		moveTrolleyBackward();
	}
	else if (key == 'k') {
		moveTrolleyForward();
	}
	else if (key == 'u') {
		moveCableUp();
	}
	else if (key == 'j') {
		moveCableDown();
	}
	else if (key == 'm') {
		hookContainer();
	}

	// Moving operaions for main camera
	else if (currentCamera->getCamera()->getName() == "Main camera") {
		switch (key) {
		case 'w':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(0.0f, 0.0f, -cameraSpeed)));
			break;

		case 'a':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(-cameraSpeed, 0.0f, 0.0f)));
			break;

		case 's':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(0.0f, 0.0f, cameraSpeed)));
			break;

		case 'd':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(cameraSpeed, 0.0f, 0.0f)));
			break;

		case ' ':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(0.0f, cameraSpeed, 0.0f)));
			break;

		case 'q':
			camera3D->setMatrix(glm::translate(camera3D->getMatrix(), glm::vec3(0.0f, -cameraSpeed, 0.0f)));
			break;
		}
	}

	if (renderingType == "Standard") {
		// Update cameras coordinate
		camera3DHook->setMatrix(glm::rotate(hook->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(-1.0f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 0.0f, -1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.5f, 0.5f)));
		camera3DCabine->setMatrix(glm::rotate(cameraVRPlaceholder->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(0.0f, -1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
	}
}

void specialKeyboardCallback(int key, int mouseX, int mouseY) {
	switch (key) {
	case KEY_UP:
		camera3D->setMatrix(glm::rotate(camera3D->getMatrix(), glm::radians(camera_sensitivity), glm::vec3(1.0f, 0.0f, 0.0f)));
		break;

	case KEY_DOWN:
		camera3D->setMatrix(glm::rotate(camera3D->getMatrix(), glm::radians(-camera_sensitivity), glm::vec3(1.0f, 0.0f, 0.0f)));
		break;

	case KEY_LEFT:
		camera3D->setMatrix(glm::rotate(camera3D->getMatrix(), glm::radians(camera_sensitivity), glm::vec3(0.0f, 1.0f, 0.0f)));
		break;

	case KEY_RIGHT:
		camera3D->setMatrix(glm::rotate(camera3D->getMatrix(), glm::radians(-camera_sensitivity), glm::vec3(0.0f, 1.0f, 0.0f)));
		break;

	case KEY_CTRL_L:
		camera3D->setMatrix(startCameraCoordinateStandard);
		break;
	}
}

void timerCallback(int value) {
	fps = frames;
	frames = 0;
	timerFlag = true;

	cout << "[CRANE]: FPS = " << fps << endl;
}


void collisionCallback(void* data) {
	glm::mat4 matrix = *reinterpret_cast<glm::mat4*>(data);

	for (const auto& pair : commands) {
		glm::mat4 wc = pair.first->getWorldCoordinateMatrix();
		// If there is a collision with a button, execute related command
		if (glm::distance(wc[3], matrix[3]) < pair.first->getRadius()) {
			pair.second();
		}
	}
}


int main(int argc, char* argv[]) {
	cout << "[Crane - SUPSI]" << endl;

	// Read config file
	ConfigReader::read("../client/app.config");
	renderingType = ConfigReader::get("RenderingType");
	std::cout << "Rendering type: " << renderingType << std::endl;

	// Initialize Engine
	Engine::init("CRANE - An OpenGL crane simulator", 650, 650, &argc, argv, renderingType);
	Engine::setKeyboardFunction(keyboardCallback);
	Engine::setTimerFunction(timerCallback); 
	Engine::setBackgroundColor(0.647f, 0.898f, 1.0f);

	// Create graphics profile
	EngineGraphics profile{};
	profile.filter = Filter::LINEAR;
	profile.wrap = TextureWrap::CLAMP_TO_EDGE;
	profile.mipmap = TextureMipmap::MIPMAP_LINEAR;
	profile.useAnisotropicFiltering = false; // NOT SUPPORTED ON VmWare Fusion...

	// Set Texture settings
	Engine::setGraphics(profile);
	Engine::load("../assets/crane/crane.ovo", "../assets/crane/");

	// Searching nodes
	root = Engine::getNode("[root]");
	crane = Engine::getNode("Crane");
	slewingUnit = Engine::getNode("SlewingUnit");
	trolley = Engine::getNode("Trolley");
	cable1 = Engine::getNode("Cable1");
	cable2 = Engine::getNode("Cable2");
	hook = Engine::getNode("Hook");
	container1 = Engine::getNode("Container1");
	container2 = Engine::getNode("Container2");
	plane = Engine::getNode("Plane");
	cabine = Engine::getNode("Cabine");
	cameraVRPlaceholder = Engine::getNode("PlaceholderCameraVR");

	// Populate commands
	Mesh* hookUp = static_cast<Mesh*>(Engine::getNode("HookUp"));
	Mesh* hookDown = static_cast<Mesh*>(Engine::getNode("HookDown"));
	Mesh* rotateLeft = static_cast<Mesh*>(Engine::getNode("RotateLeft"));
	Mesh* rotateRight = static_cast<Mesh*>(Engine::getNode("RotateRight"));
	Mesh* trolleyForward = static_cast<Mesh*>(Engine::getNode("TrolleyForward"));
	Mesh* trolleyBackward = static_cast<Mesh*>(Engine::getNode("TrolleyBackward"));
	hookButton = static_cast<Mesh*>(Engine::getNode("HookContainer"));
	commands.insert({ hookUp, moveCableUp });
	commands.insert({ hookDown, moveCableDown });
	commands.insert({ rotateLeft, rotateCounterclockwise });
	commands.insert({ rotateRight, rotateClockwise });
	commands.insert({ trolleyForward, moveTrolleyForward });
	commands.insert({ trolleyBackward, moveTrolleyBackward });
	commands.insert({ hookButton, hookContainer });

	// Disable plane shadow cast
	static_cast<Mesh*>(plane)->setShadowCast(false);

	// Set player height
	Engine::setPlayerHeight(0.0f);

	if (renderingType == "Stereoscopic") {
		// Populate cameras list
		camera3D = new PerspectiveCamera{ "Main camera", glm::mat4(1) , width, height, near, far, fov};
		camera3D->setParent(cameraVRPlaceholder);
		currentCamera = new CameraNode{ camera3D, nullptr };

		// Callbacks
		Engine::setCollisionCallback(reinterpret_cast<void (*)(void*)>(collisionCallback));
	}
	else {
		// Populate cameras list
		camera3D = new PerspectiveCamera{ "Main camera", startCameraCoordinateStandard, width, height, near, far, fov };
		camera3DHook = new PerspectiveCamera{ "Hook camera", glm::rotate(hook->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(-1.0f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 0.0f, -1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.5f, 0.5f)), width, height, near, far, fov };
		hook->addChild(camera3DHook);
		camera3DCabine = new PerspectiveCamera{ "Cabine camera", glm::rotate(cameraVRPlaceholder->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(0.0f, -1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, 0.0f)), width, height, near, far, fov };
		cabine->addChild(camera3DCabine);

		// Populate cameras list
		currentCamera = new CameraNode{ camera3D, nullptr };
		CameraNode* thirdCamera = new CameraNode{ camera3DCabine, currentCamera };
		CameraNode* secondCamera = new CameraNode{ camera3DHook, thirdCamera };
		currentCamera->setNext(secondCamera);

		Engine::setSpecialKeyboardFunction(specialKeyboardCallback);
	}

	std::string cubemapNames[6] = {
		"posx.jpg",
		"negx.jpg",
		"posy.jpg",
		"negy.jpg",
		"posz.jpg",
		"negz.jpg"
	};
	Engine::loadSkybox("../assets/skybox/", cubemapNames);

	// Start rendering some figures..
	Engine::run(display);

	// Free engine
	Engine::free();
	delete camera3D;
	delete camera3DHook;
	delete camera3DCabine;
}
