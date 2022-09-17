//
// Created by avery on 2022-09-16.
//

#pragma once

#include "poly/core/Layer.h"
#include "test.h"
class TestLayer : public Poly::Layer, public Poly::EventListener<TestEvent> {
public:
    void init() override;
    void update() override;

    void handle(TestEvent* event) override;
};
