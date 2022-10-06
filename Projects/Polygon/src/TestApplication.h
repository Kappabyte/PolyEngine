#pragma once
#include "poly/core/Application.h"
#include "TestLayer.h"

#include <poly/events/EventNode.h>

#include <iostream>

class TestApplication : public Poly::Application {
public:
	TestApplication(): Application("Test Window 1", 600, 300) {
		std::cout << "Hello, World!" << std::endl;

		pushLayer(new TestLayer(1, "Layer 1"));
		logHandler();
	}

	~TestApplication() {

	}
};

