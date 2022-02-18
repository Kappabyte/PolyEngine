#include "Test.h"

#include <iostream>
#include "events/EventNode.h"

void Test::test() {
	EventNode node;
	EventNode two(2);
	EventNode three(3);

	node.addChild(&three);
	node.addChild(&two);

	node.subscribe(this, &Test::handle);
	node.subscribe(this, &Test::handleClose);
	two.subscribe(this, &Test::handle2);
	three.subscribe(this, &Test::handleClose2);

	node.dispatch(new ExampleEvent("Hello, World!"));
	node.dispatch(new ExampleEvent("Hello, World2!"));
	node.dispatch(new ExampleEvent("Hello, World3!"));
	node.dispatch(new CloseEvent());

	node.logHandler();
}

void Test::handle(ExampleEvent* e) {
	std::cout << "1: " << e->getText().c_str() << std::endl;
}

void Test::handle2(ExampleEvent* e) {
	std::cout << "2: " << e->getText().c_str() << std::endl;
}

void Test::handleClose(CloseEvent* e) {
	std::cout << "1. Closing!" << std::endl;
	e->setCancelled(true);
}

void Test::handleClose2(CloseEvent* e) {
	std::cout << "2. Closing!" << std::endl;
}