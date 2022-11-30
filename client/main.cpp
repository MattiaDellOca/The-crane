#include "main.h"

// Create camera
PerspectiveCamera camera{"Main camera", 100, 100, 1, 100 };

void display() {
    // Clear image
    Engine::clear();

    // Render scene
    Engine::begin3D(&camera);
    Engine::render();
    Engine::end3D();

    // Swap buffers to show rendered image
    Engine::swapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
    cout << "Pressed: " << key << endl;
    if (key == ' ') {
        cout << "spacebar pressed" << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "[Crane - SUPSI]" << endl;

   // Initialize Engine
   Engine::init("My OpenGL window", 650, 650, &argc, argv);
   Engine::setKeyboardFunction(keyboardCallback);
   Engine::setBackgroundColor(0.0f, 0.0f, 0.0f);

   // Create scene graph
   Sphere s{10, glm::mat4(1), "Root"};
   Node nodeA{ "A", glm::mat4(1) };
   Node nodeB{ "B", glm::mat4(1) };
   Node nodeC{ "C", glm::mat4(1) };
   s.addChild(&nodeA);
   s.addChild(&nodeB);
   s.addChild(&nodeC);

   // Load scene graph manually
   Engine::load(&s);

   // Start rendering some figures..
   Engine::run(display);

   // Free engine
   Engine::free();
}
