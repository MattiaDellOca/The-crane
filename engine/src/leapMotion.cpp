 //////////////
 // #INCLUDE //
 //////////////

    // Header:
#include "leapMotion.h"


   // GLEW:
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>



////////////////////////
// BODY OF CLASS Leap //
////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Constructor.
 */
Leap::Leap(const std::string& name, glm::mat4 matrix) : Node(name, matrix), connection{ nullptr }, curFrame{ nullptr },
lastFrameId{ 0 }
{}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Destructor.
 */
Leap::~Leap()
{}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initializes Leap Motion connection.
 * @return TF
 */
bool LIB_API Leap::init()
{
    // Create and open connection:   
    if (LeapCreateConnection(nullptr, &connection) != eLeapRS_Success)
    {
        std::cout << "[ERROR] Unable to connect to the Leap Motion" << std::endl;
        return false;
    }
    if (LeapOpenConnection(connection) != eLeapRS_Success)
    {
        std::cout << "[ERROR] Unable to open connection to the Leap Motion" << std::endl;
        LeapDestroyConnection(connection);
        connection = nullptr;
        return false;
    }

    // Get device (only one supported):
    const uint32_t timeout = 1000;
    uint32_t computedArraySize = 0;
    for (uint32_t retry = 3; retry > 0; retry--)
    {
        LEAP_CONNECTION_MESSAGE msg;
        LeapPollConnection(connection, timeout, &msg);

        eLeapRS ret = LeapGetDeviceList(connection, nullptr, &computedArraySize);
        if (ret == eLeapRS_NotConnected)
            continue;
        else
            if (ret == eLeapRS_Success)
                if (computedArraySize)
                    break;
    }

    std::cout << "Number of available devices: " << computedArraySize << std::endl;
    if (computedArraySize != 1)
    {
        std::cout << "[ERROR] Invalid number of devices (must be 1)" << std::endl;
        LeapCloseConnection(connection);
        LeapDestroyConnection(connection);
        connection = nullptr;
        return false;
    }

    // Get ref to device:      
    if (LeapGetDeviceList(connection, &leapDevice, &computedArraySize) != eLeapRS_Success)
    {
        std::cout << "[ERROR] Unable to get ref to device" << std::endl;
        LeapCloseConnection(connection);
        LeapDestroyConnection(connection);
        connection = nullptr;
        return false;
    }

    // Done:
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Releases Leap Motion resources.
 * @return TF
 */
bool LIB_API Leap::free()
{
    // Clean up Leap Motion:
    LeapCloseConnection(connection);
    LeapDestroyConnection(connection);
    connection = nullptr;

    // Done:
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Acquire new events.
 * @return TF
 */
bool LIB_API Leap::update()
{
    const uint32_t timeout = 1000;
    LEAP_CONNECTION_MESSAGE msg;

    // Get latest update:
    int64_t now = LeapGetNow();
    int32_t frameSkipping = -1;
    do
    {
        if (LeapPollConnection(connection, timeout, &msg) != eLeapRS_Success)
        {
            std::cout << "[ERROR] Unable to poll connection" << std::endl;
            return false;
        }
        frameSkipping++;
    } while (msg.tracking_event->info.timestamp < now - 100);

    // Only tracking events are processed:
    if (msg.type != eLeapEventType_Tracking)
        return false;

    // We are lagging badly:
    if (frameSkipping > 5)
        std::cout << "[WARNING] Lag detected (" << frameSkipping << " frames skipped)" << std::endl;

    // Update only when necessary:   
    if (msg.tracking_event->tracking_frame_id > lastFrameId)
    {
        lastFrameId = msg.tracking_event->tracking_frame_id;
        curFrame = *msg.tracking_event;
    }

    // Done:
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Gets a pointer to the last updated frame.
 * @return pointer to last frame, or nullptr on error
 */
const LEAP_TRACKING_EVENT* Leap::getCurFrame() const
{
    return &curFrame;
}

void LIB_API Leap::render(glm::mat4 matrix) {
    // Update Leap Motion status:
    update();
    const LEAP_TRACKING_EVENT* l = getCurFrame();

    ShaderManager::setActiveShader("Leap Program Shader");
    Shader* shader = ShaderManager::getActiveShader();

    glBindVertexArray(m_vao);

    // Render hands using spheres:
    for (unsigned int h = 0; h < l->nHands; h++)
    {
        LEAP_HAND hand = l->pHands[h];
        glm::mat4 f = glm::translate(glm::mat4(matrix), glm::vec3(0.0f, -3.0f, -5.0f));

        shader->setVec3(shader->getParamLocation("color"), glm::vec3((float)h, (float)(1 - h), 0.5f));

        // Elbow:
        glm::mat4 c = glm::translate(glm::mat4(1.0f), glm::vec3(hand.arm.prev_joint.x, hand.arm.prev_joint.y, hand.arm.prev_joint.z));
        shader->setMatrix(shader->getParamLocation("modelview"), f * c);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertices.size());

        // Wrist:
        c = glm::translate(glm::mat4(1.0f), glm::vec3(hand.arm.next_joint.x, hand.arm.next_joint.y, hand.arm.next_joint.z));
        shader->setMatrix(shader->getParamLocation("modelview"), f * c);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertices.size());

        // Palm:
        c = glm::translate(glm::mat4(1.0f), glm::vec3(hand.palm.position.x, hand.palm.position.y, hand.palm.position.z));
        shader->setMatrix(shader->getParamLocation("modelview"), f * c);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertices.size());

        // Distal ends of bones for each digit:
        for (unsigned int d = 0; d < 5; d++)
        {
            LEAP_DIGIT finger = hand.digits[d];
            for (unsigned int b = 0; b < 4; b++)
            {
                LEAP_BONE bone = finger.bones[b];
                c = glm::translate(glm::mat4(1.0f), glm::vec3(bone.next_joint.x, bone.next_joint.y, bone.next_joint.z));
                shader->setMatrix(shader->getParamLocation("modelview"), f * c);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertices.size());
            }
        }
    }
    glBindVertexArray(0);
}

void LIB_API Leap::buildHands() {
    // Build a sphere procedurally:   
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles        
    GLfloat radius = 5.0f;
    int gradation = 10;
    for (alpha = 0.0; alpha < glm::pi<float>(); alpha += glm::pi<float>() / gradation)
        for (beta = 0.0f; beta < 2.01f * glm::pi<float>(); beta += glm::pi<float>() / gradation)
        {
            x = radius * cos(beta) * sin(alpha);
            y = radius * sin(beta) * sin(alpha);
            z = radius * cos(alpha);
            m_vertices.push_back(glm::vec3(x, y, z));
            x = radius * cos(beta) * sin(alpha + glm::pi<float>() / gradation);
            y = radius * sin(beta) * sin(alpha + glm::pi<float>() / gradation);
            z = radius * cos(alpha + glm::pi<float>() / gradation);
            m_vertices.push_back(glm::vec3(x, y, z));
        }

    // Init buffers:   
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}