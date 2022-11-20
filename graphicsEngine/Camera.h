//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "Node.h"

	// C/C++
#include <string>

	// GLM:
#include <glm/glm.hpp>


/////////////
// CLASSES //
/////////////

class Camera : public Node {
protected:
	glm::mat4 m_projection;
	float m_near;
	float m_far;
public:
	Camera(std::string, glm::mat4, glm::mat4, float, float);
	const glm::mat4& getProjection();
	const glm::mat4& getInverse();
	float getNear();
	float getFar();
	void setProjection(glm::mat4);
	void setNear(float);
	void setFar(float);
};