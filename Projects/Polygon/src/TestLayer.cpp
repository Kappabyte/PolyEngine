#include "TestLayer.h"

#include <iostream>
#include <poly/renderer/Renderer.h>

TestLayer::TestLayer(uint16_t priority, const char* name): Layer(priority), name(name) {
	subscribe(this, &TestLayer::handle);
}

void TestLayer::update() {
	Poly::Renderer::ClearColor(0, 0.8, 1.0, 1);
	Poly::Renderer::Clear();
}

void TestLayer::handle(ExampleEvent* e) {
	std::cout << "Recieved event on " << name << std::endl;
}