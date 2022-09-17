//
// Created by avery on 2022-09-13.
//
#include "test.h"
#include "TestLayer.h"
#include "poly/core/Application.h"

int main() {
//    Test* test = new Test("test");
//    test->dispatch(new TestEvent("This is a test"));
//    test->dispatch(new Test2Event("This is a test 2"));

    Poly::Application* app = Poly::Application::get();
    app->pushLayer(new TestLayer(), 1);
    app->getEventQueue()->addToQueue(new TestEvent("Test"));
    app->getEventQueue()->addToQueue(new Test2Event("Test2"));
    app->start();
    return 0;
}
