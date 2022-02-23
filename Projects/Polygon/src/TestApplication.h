#pragma once
#include "poly/core/Application.h"

#include <iostream>

class TestApplication : public Application {
public:
	TestApplication(): Application() {
		std::cout << "Hello, World!" << std::endl;

		Window* window1 = createWindow("Test Window 1", 600, 300);
		Window* window2 = createWindow("Test Window 2", 600, 300);

		window1->close();
	}

	~TestApplication() {

	}
};

