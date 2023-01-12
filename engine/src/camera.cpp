//////////////
// #INCLUDE //
//////////////
        // Library main include

#include "camera.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

/////////////
// CLASSES //
/////////////
LIB_API Camera::Camera(CameraType type, const std::string& name, glm::mat4 matrix, float nearPlane, float farPlane, unsigned int width, unsigned int height) :
    Node(name, matrix), m_near{ nearPlane }, m_far{ farPlane }, m_type{ type }, m_width{ width }, m_height{ height } {};

float LIB_API Camera::getNear() const {
    return m_near;
}
float LIB_API Camera::getFar() const {
    return m_far;
}
unsigned int LIB_API Camera::getWidth() const {
    return m_width;
}
unsigned int LIB_API Camera::getHeight() const {
    return m_height;
}
void LIB_API Camera::setWidth(unsigned int width) {
    m_width = width;
}
void LIB_API Camera::setHeight(unsigned int height) {
    m_height = height;
}
void LIB_API Camera::setNear(float n) {
    m_near = n;
}
void LIB_API Camera::setFar(float f) {
    m_far = f;
}
glm::mat4 Camera::getProperties() {
    return m_properties;
}