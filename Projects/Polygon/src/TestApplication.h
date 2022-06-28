#pragma once
#include <poly/core/Application.h>
#include "TestLayer.h"

#include <poly/events/EventNode.h>

#include <iostream>

class TestApplication : public Poly::Application {
public:
	TestApplication(): Application() {
		std::cout << "Hello, World!" << std::endl;
		Poly::EventNode node;
		node.addChild(new Poly::EventNode(5));
		node.addChild(new Poly::EventNode(10));
		node.addChild(new Poly::EventNode(1));

		node.logHandler();
		
		Poly::Window* window1 = createWindow("Test Window 1", 600, 300);
		window1->open();

		window1->pushLayer(new TestLayer(10, "Layer 1"));

		std::cout << "Logging Handler" << std::endl;
		window1->logHandler();
		std::cout << "Done Logging Handler" << std::endl;

		Poly::Window* window2 = createWindow("Test Window 2", 600, 300);
		window2->pushLayer(new TestLayer(0, "Layer 2"));
		window2->open();
	}

	~TestApplication() {

	}
};

