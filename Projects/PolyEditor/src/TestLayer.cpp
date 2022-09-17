//
// Created by avery on 2022-09-16.
//

#include "TestLayer.h"

void TestLayer::init() {
    addListener<TestEvent>(this, 0);

    std::cout << "Initialized Test Layer" << std::endl;
}

void TestLayer::update() {
}

void TestLayer::handle(TestEvent *event) {
    std::cout << "Event: " << event->getText() << std::endl;
}