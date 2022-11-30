#include "main.h"

void keyboardCallback(unsigned char key, int x, int y) {
   cout << "Pressed: " << key << endl;
   if (key == ' ') {
      cout << "spacebar pressed" << endl;
   }
}

int main(int argc, char* argv[]) {
    cout << "Hello world!" << endl;

   Engine::init("My OpenGL window", 650, 650, &argc, argv);
   cout << "ENDED CONFIG" << endl;
   Engine::setKeyboardFunction(keyboardCallback);
   Engine::setBackgroundColor(0.2f, 0.2f, 0.7f);

   Sphere s{10, glm::mat4(1), "Root"};
   Node nodeA{ "A", glm::mat4(1) };
   Node nodeB{ "B", glm::mat4(1) };
   Node nodeC{ "C", glm::mat4(1) };

   s.addChild(&nodeA);
   s.addChild(&nodeB);
   s.addChild(&nodeC);

   // Start rendering some figures..
   /*
       Engine::run([](void) {
           // Clear image
           Engine::clear();

           // Force engine to re-render entire scene!
           Engine::render();

           // Swap buffers to show rendered image
           Engine::swapBuffers();
       });
   */
   // Free engine
   // Engine::free();
}
