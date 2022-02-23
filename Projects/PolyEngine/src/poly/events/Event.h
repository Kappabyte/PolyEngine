#pragma once

#include <functional>
#include <vector>
#include <string>
#include <typeinfo>

#include "TypeInfo.h"

// Basic Event Type

class Event {
public:
	virtual ~Event() {};
	inline void setCancelled(bool cancelled) {
		this->cancelled = cancelled;
	}

	inline bool isCancelled() {
		return this->cancelled;
	}
private:
	bool cancelled = false;
};