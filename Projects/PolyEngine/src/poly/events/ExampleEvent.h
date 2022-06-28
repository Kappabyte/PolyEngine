#pragma once
#include "Event.h"
#include <string>

class ExampleEvent :
    public Event
{
public:
    ExampleEvent(std::string text): text(text) {}

    std::string getText() { return text; }
private:
    std::string text;
};

