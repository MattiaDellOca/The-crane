/**
 * @file		ovr.h
 * @brief	Self-contained helper class for interfacing OpenGL and OpenVR. Shortened version of Overvision's OvVR module.
 *
 * @author	Achille Peternier (C) SUPSI [achille.peternier@supsi.ch]
 */
#pragma once
#include "lib.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace vr
{
	struct HmdMatrix34_t;
	struct HmdMatrix44_t;
}

struct Controller;

class LIB_API OvVR
{
public:
	enum OvEye
	{
		EYE_LEFT = 0,
		EYE_RIGHT = 1,
		EYE_LAST
	};

	OvVR();
	~OvVR();

	bool init();
	bool free();
	std::string getTrackingSysName();
	bool printRenderModels();
	std::string getManufacturerName();
	std::string getModelNumber();
	unsigned int getHmdIdealHorizRes();
	unsigned int getHmdIdealVertRes();
	static glm::mat4 ovr2ogl(const vr::HmdMatrix34_t& matrix);
	static glm::mat4 ovr2ogl(const vr::HmdMatrix44_t& matrix);
	bool update();
	glm::mat4 getProjMatrix(OvEye eye, float nearPlane, float farPlane);
	glm::mat4 getEye2HeadMatrix(OvEye eye);
	glm::mat4 getModelviewMatrix();
	unsigned int getNrOfControllers();
	Controller* getController(unsigned int pos) const;
	void setReprojection(bool flag);
	void pass(OvEye eye, unsigned int eyeTexture);
	void render();


private:
	class OvVRImpl;
	OvVRImpl* impl;
	std::vector<Controller*> controllers;
};

