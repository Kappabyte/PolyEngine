#include "poly/core/Main.h"

#include "TestApplication.h"

Poly::Application* Poly::CreateApplication() {
	return new TestApplication;
}