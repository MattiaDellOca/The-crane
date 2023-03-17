#include "main.h"

// Special key definition
#define KEY_LEFT					0x0064
#define KEY_UP						0x0065
#define KEY_RIGHT					0x0066
#define KEY_DOWN					0x0067
#define KEY_SHIFT_L					0x0070
#define KEY_CTRL_L					0x0072

// Create camera
glm::mat4 startCameraCoordinate = glm::translate(glm::mat4(1.f), glm::vec3(600.f, 900.f, 1500.f));
PerspectiveCamera* camera3D = new PerspectiveCamera{ "Main camera", startCameraCoordinate, 650, 650, 1, 5000, 90 };
PerspectiveCamera* camera3DHook;
PerspectiveCamera* camera3DCabine;
OrthographicCamera* camera2D = new OrthographicCamera{ "2d Camera", glm::mat4(1), 650, 650 };

// Current camera
CameraNode* currentCamera;

// Dynamic camera parameters
float cameraSpeed = 10.0f;
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
const float heightContainer = 181.391907f;
Node* plane;
Node* cabine;

// Settings
float craneRotationSpeed = 1.f;
float cablesScaleSpeed = 0.05f;
float trolleySpeed = 0.5f;
float thresholdHook = 200.f;

// flags
bool hooked = false;
Node* hookedNode = nullptr;
float extensionsCableCount = 0;
float movementTrolleyCount = 0;

// settings flags
bool isWireframe = false;
bool isGouraund = true;

// Range of movement
const float minTrolley = -50;
const float maxTrolley = 6;
const float maxExtensionsCable = 50;

// FPS
int fps = 0;
int frames = 0;

// 2D information
// string = text to write
// int = heigh position
std::list<std::tuple<std::string, int>> information2D;

void display() {
	// Clear image
	Engine::clear();

	// Render scene
	Engine::render3D(currentCamera->getCamera());

	// Preparation list 2D information
	information2D.clear();

	// top 2D information
	unsigned int currPos = camera2D->getHeight();
	information2D.emplace_back("======= Commands =======", currPos - 20);
	information2D.emplace_back("[ g ] rotate crane counterclockwise", currPos - 35);
	information2D.emplace_back("[ l ] rotate crane clockwise", currPos - 50);
	information2D.emplace_back("[ h ] move trolley backward", currPos - 65);
	information2D.emplace_back("[ k ] move trolley forward", currPos - 80);
	information2D.emplace_back("[ u ] move cable up", currPos - 95);
	information2D.emplace_back("[ j ] move cable down", currPos - 110);

	if (hooked) {
		information2D.emplace_back("[ m ] release container", currPos - 140);
	}
	else {
		information2D.emplace_back("[ m ] hook container", currPos - 140);
	}

	if (currentCamera->getCamera()->getName() == "Main camera") {
		information2D.emplace_back("[ w a s d ] move camera", currPos - 170);
		information2D.emplace_back("[ space / q ] move camera up or down", currPos - 185);
		information2D.emplace_back("[ directional keys ] rotate camera", currPos - 200);
		information2D.emplace_back("[ LCTRL ] replace camera", currPos - 215);
		information2D.emplace_back("========================", currPos - 230);
	} else {
		information2D.emplace_back("========================", currPos - 155);
	}



	// center 2D information
	currPos = (camera2D->getHeight() - 20) / 2;
	information2D.emplace_back("======= Settings =======", currPos);
	if (isWireframe) {
		information2D.emplace_back("[ 1 ] Disable wireframe", currPos - 15);
	}
	else {
		information2D.emplace_back("[ 1 ] Enable wireframe", currPos - 15);
	}
	if (isGouraund) {
		information2D.emplace_back("[ 2 ] Disable Gouraund", currPos - 30);
	}
	else {
		information2D.emplace_back("[ 2 ] Enable Gouraund", currPos - 30);
	}
	information2D.emplace_back("[ c ] Switch camera to " + currentCamera->getNext()->getCamera()->getName(), currPos - 45);

	information2D.emplace_back("========================", currPos - 60);

	// bottom 2D information
	information2D.emplace_back("======= Information =======", 40);
	information2D.emplace_back(to_string(fps) + " fps", 25);
	information2D.emplace_back("===========================", 10);

	// Render 2D information
	Engine::render2D(camera2D, information2D);

	// Increment frame
	frames++;

	// Swap buffers to show rendered image
	Engine::swapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == '1') {
		if (isWireframe){
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
		currentCamera->getNext()->getCamera()->updateWindowSize(currentCamera->getCamera()->getWidth(), currentCamera->getCamera()->getHeight());
		currentCamera = currentCamera->getNext();
	}

	else if (key == 'g') {
		//rotate crane counterclockwise
		slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
	}
	else if (key == 'l') {
		// rotate crane counter clockwise
		slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(-craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
	}
	else if (key == 'h') {
		// move trolley backward
		if (minTrolley < movementTrolleyCount - 1) {
			trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(-trolleySpeed, 0.0f, 0.0f)));

			movementTrolleyCount--;
		}
	}
	else if (key == 'k') {
		// move trolley forward
		if (maxTrolley > movementTrolleyCount + 1) {
			trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(trolleySpeed, 0.0f, 0.0f)));

			movementTrolleyCount++;
		}
	}
	else if (key == 'u') {
		// move cable up
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
	else if (key == 'j') {
		// move cable down
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
	else if (key == 'm' && !hooked) {
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
	else if (key == 'm' && hooked) {
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

	// Update cameras coordinate
	camera3DHook->setMatrix(glm::rotate(hook->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(-1.0f, 0.f,0.f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 0.0f, -1.0f)));
	camera3DCabine->setMatrix(glm::rotate(cabine->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(0.0f, -1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
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
		camera3D->setMatrix(startCameraCoordinate);
		break;
	}
}

void timerCallback(int value) {
	fps = frames;
	frames = 0;

	cout << "[CRANE]: FPS = " << fps << endl;
}

int main(int argc, char* argv[]) {
	cout << "[Crane - SUPSI]" << endl;

	// Initialize Engine
	Engine::init("CRANE - An OpenGL crane simulator", 650, 650, &argc, argv);
	Engine::setKeyboardFunction(keyboardCallback);
	Engine::setSpecialKeyboardFunction(specialKeyboardCallback);
	Engine::setTimerFunction(timerCallback);  // Set up timer

	Engine::setBackgroundColor(0.647f, 0.898f, 1.0f);

	// Create graphics profile
	EngineGraphics profile{};
	profile.filter = Filter::LINEAR;
	profile.wrap = TextureWrap::CLAMP_TO_EDGE;
	profile.mipmap = TextureMipmap::MIPMAP_LINEAR;
	profile.useAnisotropicFiltering = false; // NOT SUPPORTED ON VmWare Fusion...

	// Set Texture settings
	Engine::setGraphics(profile);
	Engine::load("../assets/crane/crane_plane.ovo", "../assets/crane/");

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

	// Disable plane shadow cast
	static_cast<Mesh*>(plane)->setShadowCast(false);

	// Additional cameras
	camera3DHook = new PerspectiveCamera{ "Hook camera", glm::rotate(hook->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(-1.0f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 0.0f, -1.0f)), camera3D->getWidth(), camera3D->getHeight(), 1, 10000, 90 };
	hook->addChild(camera3DHook);

	// Calculate cabine matrix
	camera3DCabine = new PerspectiveCamera{ "Cabine camera", glm::rotate(cabine->getWorldCoordinateMatrix(), glm::radians(90.f), glm::vec3(0.0f, -1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, 0.0f)), camera3D->getWidth(), camera3D->getHeight(), 1, 10000, 90 };
	cabine->addChild(camera3DCabine);

	// Populate cameras list
	currentCamera = new CameraNode{ camera3D, nullptr };
	CameraNode* thirdCamera = new CameraNode{ camera3DCabine, currentCamera };
	CameraNode* secondCamera = new CameraNode{ camera3DHook, thirdCamera };
	currentCamera->setNext(secondCamera);

	// Start rendering some figures..
	Engine::run(display);

	// Free engine
	Engine::free();
	delete camera2D;
	delete camera3D;
	delete camera3DHook;
	delete camera3DCabine;
}
