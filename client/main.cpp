#include "main.h"

// Create camera
PerspectiveCamera camera{"Main camera", 100, 100, 1, 100 };

// ====== LISTA DI COSE DA FARE ======

// 1 - Implementare list per rendering + rendering luci prima del resto della scena
// 2 - Aggiornare parametri della camera al reshape
// 3 - Per waring: o pragma per disabilitarli o struttura pimpl

void display() {
    // Clear image
    Engine::clear();

    // Render scene
    Engine::begin3D(&camera); // set camera
    Engine::render(); // render scene
    Engine::end3D(); // remove camera

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

   // Instantiate material
   // EMERALD -> http://devernay.free.fr/cours/opengl/materials.html
   Material emerald{ "Green" };
   emerald.setAmbient({ glm::vec4(0.0215f, 0.1745f, 0.0215f, 1.0f) });
   emerald.setDiffuse({ glm::vec4(0.07568f, 0.61424f, 0.07568f, 1.0f) });
   emerald.setSpecular({ glm::vec4(0.633f, 0.727811f, 0.633f, 1.0f) });
   emerald.setShininess(0.6f * 128);

   // Create scene graph
   Sphere s{10.0f,  "Root", glm::mat4(1), emerald };
   Cube nodeA{ 5.0f, "A", glm::mat4(1), emerald };
   Cube nodeB{ 10.0f, "B", glm::mat4(1), emerald };
   Sphere nodeC{ 5.0f, "C", glm::mat4(1), emerald };
   Sphere nodeD{ 5.0f, "D", glm::mat4(1), emerald };
   Light light{ "Light", glm::mat4(1) };
   s.addChild(&nodeA);
   s.addChild(&nodeB);
   s.addChild(&nodeC);
   nodeA.addChild(&nodeD);
   nodeA.addChild(&light);

   // Load scene graph manually
   Engine::load(&s);

   // Start rendering some figures..
   Engine::run(display);

   // Free engine
   Engine::free();
}
