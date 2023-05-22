#include <iostream>
#include "src/engine.h"
#include "src/camera.h"
#include "src/node.h"
#include "src/orthographicCamera.h"
#include "src/perspectiveCamera.h"
#include "src/light.h"
#include "src/directionalLight.h"
#include "src/omnidirectionalLight.h"
#include "src/spotLight.h"

#include "cameraNode.h"
#include "configReader.h"

using namespace std; 

glm::mat4 calculateWorldCoordinates(Node* node, glm::mat4 matrix);
