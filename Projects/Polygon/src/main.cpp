#include "poly/core/Main.h"

#include "TestApplication.h"

int main() {
	Poly::Application* application = new TestApplication();

	application->start();
}