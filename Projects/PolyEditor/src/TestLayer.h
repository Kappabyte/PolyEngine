//
// Created by avery on 2022-09-16.
//

#pragma once

#include "poly/core/Layer.h"
class TestLayer : public Poly::Layer {
public:
    void init() override;
    void update() override;
};
