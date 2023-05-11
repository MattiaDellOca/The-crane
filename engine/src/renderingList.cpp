#include "renderingList.h"
#include "shaderManager.h"

// GLEW:
#include <GL/glew.h>

LIB_API RenderingList::RenderingList(const std::string& name) :
	Object(name) { };

LIB_API RenderingList::~RenderingList() {}

void RenderingList::loadRenderNode(RenderNode* node) {
	if (dynamic_cast<const Light*>(node->m_node) != nullptr)
		m_list.push_front(node);
	else
		m_list.push_back(node);
}

std::list<RenderNode*> LIB_API RenderingList::getRenderingList() {
	return m_list;
}


void LIB_API RenderingList::pass(Node* node, glm::mat4 parentMatrix) {
	if (node == NULL)
		return;

	// Matrix expressed in world coordinates
	glm::mat4 wcMatrix = parentMatrix * node->getMatrix();


	// If concrete type of node is either Mesh or Light (therefore NOT Camera), load it in the rendering list,
	// otherwise skip the operation!
	if (dynamic_cast<const Camera*>(node) == nullptr && (dynamic_cast<const Light*>(node) != nullptr || dynamic_cast<const Node*>(node) != nullptr)) {
		loadRenderNode(new RenderNode{ node, wcMatrix });
	}

	if (node->getNumberOfChildren() > 0) {
		for (auto* child : node->getChildren()) {
			pass(child, wcMatrix);
		}
	}
}

void LIB_API RenderingList::clear() {
	m_list.clear();
}

void LIB_API RenderingList::render(glm::mat4 cameraMatrix) {
	glm::mat4 inverseCameraMatrix = glm::inverse(cameraMatrix);

	std::vector<RenderNode*> lights;

	// Remove the first n elements from m_list that are lights
	// Get all lights
	// and add them to the lights list
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		if (dynamic_cast<Light*>((*it)->m_node) != nullptr) {
			lights.push_back(*it);
		}
		else {
			// m_list is sorted, so if a *non* light is encounter, the for can be break
			break;
		}
	}
	int nrLights = static_cast<int>(lights.size());

	// Remove the lights from the rendering list
	for (auto it = lights.begin(); it != lights.end(); ++it) {
		m_list.remove(*it);
	}


	// render
	for (size_t i = 0; i < lights.size(); i++) {

		// light 0 is the only light that is not additive
		if (i == 0) {
			glDepthFunc(GL_LESS);
		}

		// Enable addictive blending from light 1 on:
		if (i == 1) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthFunc(GL_LEQUAL);
		}

		// Get first light
		RenderNode* light = lights.at(i);

		// Get the light type
		LightType lightType = dynamic_cast<Light*>(light->m_node)->getLightType();

		// Set active shader
		std::string shaderName = "programShader";

		if (lightType == LightType::DIRECTIONAL)
			shaderName += "Directional";
		else if (lightType == LightType::OMNIDIRECTIONAL)
			shaderName += "Omnidirectional";
		else {
			shaderName += "Spot";
		}
		shaderName += "Light";

		// Set active shader
		ShaderManager::setActiveShader(shaderName);
		ShaderManager::getActiveShader()->setInt(ShaderManager::getActiveShader()->getParamLocation("nrLights"), static_cast<int>(lights.size()));

		m_camera->render(glm::mat4(1.f));

		// Render light
		dynamic_cast<Light*>(light->m_node)->render(inverseCameraMatrix * light->m_mat);


		// Normal rendering
		for (auto it = m_list.begin(); it != m_list.end(); ++it) {
			// call render method for each node
			(*it)->m_node->render(inverseCameraMatrix * (*it)->m_mat);
		}

	}
	// Disable blending, in case we used it:
	if (lights.size() > 1) {
		glDisable(GL_BLEND);
		glDepthFunc(GL_LESS);
	}
}