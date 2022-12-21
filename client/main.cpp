#include "main.h"

// Create camera
PerspectiveCamera camera3d{"Main camera", 100, 100, 1, 100 };
OrthographicCamera camera2d{ "2d Camera", 100, 100 }; // TODO: Write "wireframe" option in 2D UI (it is supported but not shown to the user)

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
    cout << "Pressed: " << key << endl;
    if (key == 'w') {
        cout << "[CRANE] Info: Toggling wireframe.." << endl;
        Engine::toggleWireframe();
    }
}

int main(int argc, char* argv[]) {
    cout << "[Crane - SUPSI]" << endl;

   // Initialize Engine
   Engine::init("CRANE - An OpenGL crane simulator", 650, 650, &argc, argv);
   Engine::setKeyboardFunction(keyboardCallback);
   Engine::setBackgroundColor(0.0f, 0.0f, 0.0f);

   Texture t{ "Teapot", "C:\\Users\\Luca\\Desktop\\cg_2dFileFormatsExamples\\teapot_rle.tga"};

   // Instantiate material
   Material emerald{ "Emerald" };
   emerald.setAmbient({ glm::vec4(0.0215f, 0.1745f, 0.0215f, 1.0f) });
   emerald.setDiffuse({ glm::vec4(0.07568f, 0.61424f, 0.07568f, 1.0f) });
   emerald.setSpecular({ glm::vec4(0.633f, 0.727811f, 0.633f, 1.0f) });
   emerald.setShininess(0.6f * 128);
   emerald.setTexture(&t);
   
   // Create scene graph
   Cube b{ 2.0f, "A", glm::mat4(1.0f), &emerald};
   
   // Load scene graph manually
   Engine::load(&b);

   // Start rendering some figures..
   Engine::run(display);

   // Free engine
   Engine::free();
}
