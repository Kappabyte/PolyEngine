//
// Created by avery on 2022-09-16.
//

#include "TestLayer.h"
#include "poly/core/Application.h"
#include "poly/core/Window.h"
#include <poly/render/Renderer.h>

void TestLayer::init() {
    std::cout << "TestLayer init" << std::endl;
}

void TestLayer::update() {
    Poly::Renderer::begin(Poly::Application::get()->getWindow("poly:Test"));

    Poly::Renderer::draw(Poly::Shared<Poly::Mesh>(), Poly::Shared<Poly::Material>());

    Poly::Renderer::end();
}