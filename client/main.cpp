#include "main.h"
int main(int argc, char* argv[]) {
   cout << "Hello world!" << endl;
   DynLib::init();
   DynLib::doNothing();
   DynLib::free();

}
