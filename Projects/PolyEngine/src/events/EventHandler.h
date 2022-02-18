#pragma once
#include "Event.h"

class HandlerFunctionBase {
public:
	virtual ~HandlerFunctionBase() {};
	const void exec(Event* event) { call(event); }
private:
	virtual void call(Event*) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
public:
	typedef void (T::* MemberFunc)(EventType*);
	MemberFunctionHandler(T* instance, MemberFunc func) {
		this->f = func;
		this->instance = instance;
	};
	void call(Event* event) {
		(instance->*f)(static_cast<EventType*>(event));
	}

private:
	MemberFunc f;
	T* instance;
};
