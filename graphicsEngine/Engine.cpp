//////////////
// #INCLUDE //
//////////////

	// Project classes
#include "Engine.h"

	// C/C++
#include <iostream>


/////////////
// CLASSES //
/////////////

Engine* Engine::getInstance() {
	static Engine* m_instance;
	if (!m_instance)
		m_instance = new Engine();
	return m_instance;
}

void Engine::init() {
	std::cout << "Function init still needs to be implemented!" << std::endl;
}

Node* Engine::load(std::string) {
	std::cout << "Function load still needs to be implemented!" << std::endl;
	return nullptr;
}

void Engine::clear() {
	std::cout << "Function clear still needs to be implemented!" << std::endl;
}

void Engine::begin3D(Camera camera) {
	std::cout << "Function begin3D still needs to be implemented!" << std::endl;
}

void Engine::end3D() {
	std::cout << "Function end3D still needs to be implemented!" << std::endl;
}

void Engine::swap() {
	std::cout << "Function swap still needs to be implemented!" << std::endl;
}

void Engine::free() {
	std::cout << "Function free still needs to be implemented!" << std::endl;
}