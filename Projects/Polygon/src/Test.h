#pragma once

#include <events/ExampleEvent.h>

class Test
{
public:
	void test();
	void handle(ExampleEvent* e);
	void handle2(ExampleEvent* e);
	void handleClose(CloseEvent* e);
	void handleClose2(CloseEvent* e);
};

