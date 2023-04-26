//
// Created by avery on 2022-09-13.
//
#include "TestLayer.h"
#include "poly/core/Application.h"
#include "poly/render/Buffer.h"
#include "poly/systems/Registry.h"

int main() {
    Poly::Application* app = Poly::Application::get();
    app->addWindow("test");
    app->setApi(Poly::RenderAPI::GL);
    app->pushLayer(new TestLayer(), 1);
    app->start();
    Poly::Shared<Poly::Registry<Poly::JsonRegistryData>> reg = Poly::Registry<Poly::JsonRegistryData>::getRegistry("data/items");
    auto sword = (*reg).getFile("test:sword").getData();
    LOG_INFO(sword.dump());
    return 0;
}
