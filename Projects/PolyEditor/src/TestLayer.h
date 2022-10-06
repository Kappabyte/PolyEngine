//
// Created by avery on 2022-09-16.
//

#pragma once

#include "poly/core/Layer.h"
#include "poly/util/Ref.h"
#include "poly/render/geometry/mesh/Mesh.h"
#include "poly/render/geometry/material/Material.h"

class TestLayer : public Poly::Layer {
public:
    void init() override;
    void update() override;
private:
    Poly::Shared<Poly::Mesh> mesh;
    Poly::Shared<Poly::Material> material;
};
