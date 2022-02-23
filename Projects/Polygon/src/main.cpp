#include "core/Main.h"

#include "TestApplication.h"

Application* CreateApplication() {
	return new TestApplication;
}