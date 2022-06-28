#include <poly/core/Application.h>

#include "TestApplication.h"

Poly::Application* Poly::CreateApplication() {
	return new TestApplication;
}