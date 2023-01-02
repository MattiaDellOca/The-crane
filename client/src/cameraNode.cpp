#include "cameraNode.h"

CameraNode::CameraNode(PerspectiveCamera* camera, CameraNode* next) : m_camera(camera), m_next(next) {};

CameraNode* CameraNode::getNext() {
	return m_next;
}

void CameraNode::setNext(CameraNode* next) {
	m_next = next;
}
PerspectiveCamera* CameraNode::getCamera() {
	return m_camera;
}

CameraNode::~CameraNode()
{
	delete m_camera;
	delete m_next;
}