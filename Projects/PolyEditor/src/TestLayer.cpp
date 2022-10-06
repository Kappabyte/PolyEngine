//
// Created by avery on 2022-09-16.
//

#include "TestLayer.h"
#include "poly/core/Application.h"
#include "poly/core/Window.h"
#include "poly/render/geometry/Geometry.h"
#include <poly/render/Renderer.h>

void TestLayer::init() {
    std::cout << "TestLayer init" << std::endl;

    mesh = Poly::MakeShared<Poly::Mesh>();
    float a_Pos[] =  {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    mesh->addVertexAttribute("a_Pos", Poly::ShaderType::FLOAT3, a_Pos, sizeof(a_Pos));
    float a_Color[] = {
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
    };
    mesh->addVertexAttribute("a_Color", Poly::ShaderType::FLOAT3, a_Color, sizeof(a_Color));
    material = Poly::MakeShared<Poly::Material>(nullptr);
}

void TestLayer::update() {
    Poly::Renderer::begin(Poly::Application::get()->getWindow("poly:Test"));

    Poly::Renderer::draw(mesh, material);

    Poly::Renderer::end();
}