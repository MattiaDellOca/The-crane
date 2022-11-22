#include "main.h"

void keyboardCallback(unsigned char key, int x, int y) {
   cout << "Pressed: " << key << endl;
   if (key == ' ') {
      cout << "spacebar pressed" << endl;
   }
}

int main(int argc, char* argv[]) {
   cout << "Hello world!" << endl;
   Engine::init("My OpenGL window", 650, 650);
   Engine::setKeyboardFunction(keyboardCallback);
   Engine::setBackgroundColor(0.2f, 0.2f, 0.7f);

   while (Engine::isRunning()) {
       while (true) {
          // Clear image
          Engine::clear();

          // Force engine to re-render everything!
          Engine::render();
        
          // Swap buffers!
          Engine::swapBuffers(); 
       }
   } 

   Engine::free();
   return 0;
}
