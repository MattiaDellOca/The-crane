#include "main.h"

void myKeyboardCallback(unsigned char key, int x, int y) {

   if (key == ' ') {
      cout << "spacebar pressed" << endl;
   }
}


int main(int argc, char* argv[]) {
   cout << "Hello world!" << endl;
   DynLib::init();
   /*
   MyEngine::init("My OpenGL window", 640, 480);
   MyEngine::setKeyboardCallback(myKeyboardCallback);
   MyEngine::setBackgroundColor(0.2f, 0.2f, 0.7f);
   //while (MyEngine::isRunning()) {
   while (true) {

   
      MyEngine::clearWindow();
      
      //draw Something
      MyEngine::doSomething();
      
      MyEngine::swapBuffers(); 
   }
      //} 
   MyEngine::free();
   */
   return 0;


}
