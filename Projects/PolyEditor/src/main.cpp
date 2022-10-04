//
// Created by avery on 2022-09-13.
//
#include "TestLayer.h"
#include "poly/core/Application.h"
#include "poly/render/Buffer.h"

int main() {
    Poly::Application* app = Poly::Application::get();
    app->addWindow(Poly::NamespaceID("Test"));
    app->setAPI(Poly::API::GL);
    app->pushLayer(new TestLayer(), 1);
    app->start();
    return 0;
}
