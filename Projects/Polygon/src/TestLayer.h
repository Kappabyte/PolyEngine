#pragma once

#include <poly/layers/Layer.h>
#include <poly/events/ExampleEvent.h>

class TestLayer : public Poly::Layer {
public:
	TestLayer(uint16_t priority, const char* name);
	void update() override;

	void handle(ExampleEvent* e);
private:
	const char* name;
};