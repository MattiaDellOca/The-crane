#include "main.h"

// Create camera
glm::mat4 startCamera = glm::translate(glm::mat4(1.f), glm::vec3(600.f,900.f,1500.f));
PerspectiveCamera* camera3d = new PerspectiveCamera{ "Main camera", startCamera, 650, 650, 1, 10000, 90 };
OrthographicCamera camera2d{ "2d Camera", glm::mat4(1), 650, 650 }; // TODO: Write "wireframe" option in 2D UI (it is supported but not shown to the user)

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

// Settings
float cameraSpeed = 100.0f;
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
	Engine::begin3D(camera3d); // set camera
	Engine::render3D(); // render scene
	Engine::end3D(); // remove camera

	Engine::begin2D(&camera2d);

	information2D.clear();
	// top 2D information 
	unsigned int currPos = camera2d.getHeight();
	information2D.emplace_back("======= Commands =======", currPos - 20);
	information2D.emplace_back("[ w a s d ] move camera", currPos - 35);
	information2D.emplace_back("[ g ] rotate crane counterclockwise", currPos - 50);
	information2D.emplace_back("[ l ] rotate crane clockwise", currPos - 65);
	information2D.emplace_back("[ h ] move trolley backward", currPos - 80);
	information2D.emplace_back("[ k ] move trolley forward", currPos - 95);
	information2D.emplace_back("[ u ] move cable up", currPos - 110);
	information2D.emplace_back("[ j ] move cable down", currPos - 125);

	if (hooked) {
		information2D.emplace_back("[ m ] release container", currPos - 140);
	}
	else {
		information2D.emplace_back("[ m ] hook container", currPos - 140);
	}
	information2D.emplace_back("========================", currPos - 155);

	// center 2D information
	currPos = (camera2d.getHeight() - 20) / 2;
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
	information2D.emplace_back("========================", currPos - 45);

	// bottom 2D information
	information2D.emplace_back("======= Information =======", 40);
	information2D.emplace_back(to_string(fps) + " fps", 25);
	information2D.emplace_back("===========================", 10);

	Engine::render2D(information2D);
	Engine::end2D();

	// Increment frame
	frames++;

	// Swap buffers to show rendered image
	Engine::swapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if (key == '1' && isWireframe) {
		cout << "[CRANE] Settings: Disable wireframe" << endl;
		Engine::disableWireframe();
		isWireframe = !isWireframe;
	} 
	else if (key == '1' && !isWireframe) {
		cout << "[CRANE] Settings: Enable wireframe" << endl;
		Engine::enableWireframe();
		isWireframe = !isWireframe;
	}
	else if (key == '2' && isGouraund) {
		cout << "[CRANE] Settings: Enable Gouraund shading" << endl;
		Engine::enableGouraund();
		isGouraund = !isGouraund;
	}
	else if (key == '2' && !isGouraund) {
		cout << "[CRANE] Settings: Gouraund shading" << endl;
		Engine::enableGouraund();
		isGouraund = !isGouraund;
	}
	else if (key == 'w') {
		cout << "[CRANE] Camera: moving frontward" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(0.0f, 0.0f, -cameraSpeed)));
	}
	else if (key == 'a') {
		cout << "[CRANE] Camera: moving left" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(-cameraSpeed, 0.0f, 0.0f)));
	}
	else if (key == 's') {
		cout << "[CRANE] Camera: moving backward" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(0.0f, 0.0f, cameraSpeed)));
	}
	else if (key == 'd') {
		cout << "[CRANE] Camera: moving right" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(cameraSpeed, 0.0f, 0.0f)));
	}
	else if (key == ' ') {
		cout << "[CRANE] Camera: moving up" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(0.0f, cameraSpeed, 0.0f)));
	}
	else if (key == 'q') {
		cout << "[CRANE] Camera: moving down" << endl;
		camera3d->setMatrix(glm::translate(camera3d->getMatrix(), glm::vec3(0.0f, -cameraSpeed, 0.0f)));
	}
	else if (key == 'g') {
		//rotate crane counterclockwise
		cout << "[CRANE] SleewingUnit: rotating counterclockwise" << endl;
		slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
	}
	else if (key == 'l') {
		// rotate crane counter clockwise
		cout << "[CRANE] SleewingUnit: rotating clockwise" << endl;
		slewingUnit->setMatrix(glm::rotate(slewingUnit->getMatrix(), glm::radians(-craneRotationSpeed), glm::vec3(0.0f, 1.f, 0.f)));
	}
	else if (key == 'h') {
		// move trolley backward

		if (minTrolley < movementTrolleyCount - 1) {
			cout << "[CRANE] Trolley: moving backward" << endl;
			trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(-trolleySpeed, 0.0f, 0.0f)));

			movementTrolleyCount--;
		}
		else {
			cout << "[CRANE] Trolley: can't moving backward" << endl;
		}
	}
	else if (key == 'k') {
		// move trolley forward
		if (maxTrolley > movementTrolleyCount + 1) {
			cout << "[CRANE] Trolley: moving forward" << endl;
			trolley->setMatrix(glm::translate(trolley->getMatrix(), glm::vec3(trolleySpeed, 0.0f, 0.0f)));

			movementTrolleyCount++;
		}
		else {
			cout << "[CRANE] Trolley: can't moving forward" << endl;
		}
	}
	else if (key == 'u') {
		// move cable up

		if (extensionsCableCount > 0) {
			cout << "[CRANE] Cables: moving up" << endl;
 
			// There is an object between the hook and the cable
			Node* hookParent = cable1->getChildren().at(0);

			cable1->setMatrix(glm::scale(cable1->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));
			cable2->setMatrix(glm::scale(cable2->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));

			// adapt matrix
			hookParent->setMatrix(glm::scale(hookParent->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));

			extensionsCableCount--;
		}
		else {
			cout << "[CRANE] Cables: can't moving up" << endl;
		}
	}
	else if (key == 'j') {
		// move cable down

		if (maxExtensionsCable > extensionsCableCount + 1) {
			cout << "[CRANE] Cables: moving down" << endl;

			// There is an object between the hook and the cable
			Node* hookParent = cable1->getChildren().at(0);

			cable1->setMatrix(glm::scale(cable1->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));
			cable2->setMatrix(glm::scale(cable2->getMatrix(), glm::vec3(1.0f, 1.0f + cablesScaleSpeed, 1.0f)));

			// adapt matrix
			hookParent->setMatrix(glm::scale(hookParent->getMatrix(), glm::vec3(1.0f, 1.0f - cablesScaleSpeed, 1.0f)));

			extensionsCableCount++;
		}
		else {
			cout << "[CRANE] Cables: can't moving down" << endl;
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
			cout << "[CRANE] Hook: hooking container1" << endl;

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
			cout << "[CRANE] Hook: hooking container2" << endl;

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
		else {
			cout << "[CRANE] Hook: The containers are too far apart" << endl;
		}
	}
	else if (key == 'm' && hooked) {
		// Get world coordinates
		glm::vec3 worldObjHooked{ hookedNode->getWorldCoordinateMatrix()[3] };
		glm::vec3 worldCordPlane{ plane->getWorldCoordinateMatrix()[3] };
		// Calculate distance
		float distanceObjPlane = worldObjHooked.y - worldCordPlane.y - heightContainer;
		cout << distanceObjPlane << endl;

		if (distanceObjPlane < abs(thresholdHook)) {
			// Release the container
			cout << "[CRANE] Hook: release object" << endl;
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
		else {
			cout << "[CRANE] Hook: the container is too far from the plane" << endl;
		}
		//hooked = !hooked;
	}
	else {
		cout << key << " not supported" << endl;
	}
}

void timerCallback(int value) {
	fps = frames;
	frames = 0;
}

int main(int argc, char* argv[]) {
	cout << "[Crane - SUPSI]" << endl;

	// Initialize Engine
	Engine::init("CRANE - An OpenGL crane simulator", 650, 650, &argc, argv);
	Engine::setKeyboardFunction(keyboardCallback);
	Engine::setTimerFunction(timerCallback);  // Set up timer

	Engine::setBackgroundColor(0.647f, 0.898f, 1.0f);

	// Create graphics profile
	EngineGraphics profile{};
	profile.filter = Filter::LINEAR;
	profile.mipmap = TextureMipmap::MIPMAP_LINEAR;
	profile.useAnisotropicFiltering = true;
	profile.anisotropicFilteringValue = 2;

	// Set Texture settings
	Engine::setGraphics(profile);
	Engine::load("..\\assets\\crane\\crane.ovo", "..\\assets\\crane");

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

	// Start rendering some figures..
	Engine::run(display);

	// Free engine
	Engine::free();
}	
