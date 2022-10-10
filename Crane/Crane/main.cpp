#include "main.h"

int main(int argc, char *argv[]) {
	cout << "Hello world!" << endl;
	SimpleDynLib::init();
	SimpleDynLib::doNothing();
	SimpleDynLib::free();
}