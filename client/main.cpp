#include "main.h"

// Create camera
PerspectiveCamera camera{"Main camera", 100, 100, 1, 100 };

// Create rendering list
RenderingList m_list{ "Rendering list" };

// ====== LISTA DI COSE DA FARE ======

// 1 - Implementare list per rendering + rendering luci prima del resto della scena
// 2 - Aggiornare parametri della camera al reshape

void display() {
    // Clear image
    Engine::clear();

    // Render scene
    Engine::begin3D(&camera);
    Engine::render(&camera, &m_list);
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
   Sphere s{10.0f,  "Root", glm::mat4(1) };
   Cube nodeA{ 5.0f, "A", glm::mat4(1) };
   Cube nodeB{ 10.0f, "B", glm::mat4(1) };
   Sphere nodeC{ 5.0f, "C", glm::mat4(1) };
   s.addChild(&nodeA);
   s.addChild(&nodeB);
   s.addChild(&nodeC);

   m_list.pass(s);

   Engine::render(&camera, &m_list);

   // Load scene graph manually
   //Engine::load(&s);

   // Start rendering some figures..
   Engine::run(display);

   // Free engine
   Engine::free();
}
