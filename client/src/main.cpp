#include "main.h"

// Create camera
PerspectiveCamera camera3d{ "Main camera", glm::mat4(1), 100, 100, 1, 1000, 90};
OrthographicCamera camera2d{ "2d Camera", glm::mat4(1), 100, 100 }; // TODO: Write "wireframe" option in 2D UI (it is supported but not shown to the user)
float cameraSpeed = 10.0f;

// ====== LISTA DI COSE DA FARE ======
// 1 - Aggiornare parametri della camera al reshape
// 2 - Per warning: o pragma per disabilitarli o struttura pimpl

void display() {
    // Clear image
    Engine::clear();

    // Render scene
    Engine::begin3D(&camera3d); // set camera
    Engine::render(); // render scene
    Engine::end3D(); // remove camera

    // Swap buffers to show rendered image
    Engine::swapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
    if (key == 'x') {
        cout << "[CRANE] Info: Toggling wireframe.." << endl;
        Engine::toggleWireframe();
    }
    else if(key == 'w') {
        cout << "[CRANE] Camera: moving frontward" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(0.0f, 0.0f, -cameraSpeed)));
    }
    else if (key == 'a') {
        cout << "[CRANE] Camera: moving left" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(-cameraSpeed, 0.0f, 0.0f)));
    }
    else if (key == 's') {
        cout << "[CRANE] Camera: moving backward" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(0.0f, 0.0f, cameraSpeed)));
    }
    else if (key == 'd') {
        cout << "[CRANE] Camera: moving right" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(cameraSpeed, 0.0f, 0.0f)));
    }
    else if (key == ' ') {
        cout << "[CRANE] Camera: moving up" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(0.0f, cameraSpeed, 0.0f)));
    }
    else if (key == 'q') {
        cout << "[CRANE] Camera: moving down" << endl;
        camera3d.setMatrix(glm::translate(camera3d.getMatrix(), glm::vec3(0.0f, -cameraSpeed, 0.0f)));
    }
}



int main(int argc, char* argv[]) {
    cout << "[Crane - SUPSI]" << endl;

   // Initialize Engine
   Engine::init("CRANE - An OpenGL crane simulator", 650, 650, &argc, argv);
   Engine::setKeyboardFunction(keyboardCallback);
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

   // Start rendering some figures..
   Engine::run(display);

   // Free engine
   Engine::free();
}
