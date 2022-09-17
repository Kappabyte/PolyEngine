//
// Created by avery on 2022-09-13.
//

#pragma once

#include <poly/events/EventNodeBase.h>

#include <iostream>
#include "poly/events/EventNode.h"

class TestEvent : public Poly::Event {
public:
    TestEvent(std::string text) : text(text) {}

    inline std::string getText() { return text; }
private:
    std::string text;
};

class Test2Event : public Poly::Event {
public:
    Test2Event(std::string text) : text(text) {}

    inline std::string getText() { return text; }
private:
    std::string text;
};

class Test: public Poly::EventNode, public Poly::EventListener<TestEvent>, public Poly::EventListener<Test2Event>, public Poly::EventResultListener<TestEvent>, public Poly::EventResultListener<Test2Event> {
public:
    Test(std::string name, uint8_t depth = 3): name(name + std::to_string(depth)) {
        addListener<TestEvent>(this, 4);
        addListener<Test2Event>(this, 4);
        addResultListener<TestEvent>(this, 0);
        addResultListener<Test2Event>(this, 0);

        if(depth > 1) {
            addChild(new Test(name, depth - 1), 0);
        }
    }

    void handle(TestEvent *event) override {
        std::cout << "(" << name << ") Test 1: " << event->getText() << std::endl;
    };

    void handle(Test2Event *event) override {
        std::cout << "(" << name << ") Test 2: " << event->getText() << std::endl;
    };

    void handleResult(TestEvent* event, bool& propagateResult) override {
        std::cout << "(" << name << ") Handled Result 1: " << event->getText() << std::endl;
        propagateResult = false;
    }

    void handleResult(Test2Event* event, bool& propagateResult) override {
        std::cout << "(" << name << ") Handled Result 2: " << event->getText() << std::endl;
        propagateResult = false;
    }

    std::string name;
};