#pragma once
#include "Event.h"
#include <map>
#include <list>
#include "EventHandler.h"

//TODO: Clean up this file!

class EventNode {
public:
	EventNode(uint32_t priority): priority(priority) {}
	EventNode() : priority(0) {}

	template<class T, class EventType>
	inline void subscribe(T* executor, void (T::* handler)(EventType*)) {
		if (handlers.find(TypeInfo(&typeid(EventType))) == handlers.end()) {
			handlers.insert({ TypeInfo(&typeid(EventType)), new std::vector<HandlerFunctionBase*> });
		}

		auto eventHandlers = handlers.find(TypeInfo(&typeid(EventType)))->second;
		eventHandlers->push_back(new MemberFunctionHandler<T, EventType>(executor, handler));
	}

	inline void dispatch(Event* e) {
		auto ype = typeid(*e).name();

		//Try to handle the event in a local handler first
		HandlerList::iterator it = handlers.find(TypeInfo(&typeid(*e)));
		if (it != handlers.end()) {
			//Go through each registered handler and execute it, cancelling if the event was cancelled
			auto test = it->first;
			std::vector<HandlerFunctionBase*>::iterator iter = it->second->begin();
			while (iter != it->second->end()) {
				(*iter)->exec(e);
				if (e->isCancelled()) {
					return;
				}
				iter++;
			}
		}

		//Pass event to child nodes if the event could not be handled, or if it was cancelled.
		std::list<EventNode*> children = getChildren();
		for (std::list<EventNode*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			(*iter)->dispatch(e);
			if (e->isCancelled()) {
				return;
			}
		}
	}

	inline void addChild(EventNode* node) {
		children.insert(std::lower_bound(children.begin(), children.end(), node), node);
	}

	virtual inline uint16_t getPriority() const {
		return priority;
	}

	virtual inline std::list<EventNode*> getChildren() {
		return children;
	}

	bool operator< (const EventNode*& object) const {
		return object->getPriority() < getPriority();
	}

	void logHandler() {
		uint16_t depth = 0;

		printf(logHandler(depth).c_str());
	}
private:
	typedef std::map<TypeInfo, std::vector<HandlerFunctionBase*>*> HandlerList;
	HandlerList handlers;

	uint32_t priority;

	std::list<EventNode*> children;

	std::string logHandler(uint16_t depth) {
		std::string result = "\n";
		for (uint16_t i = 0; i < depth; i++) result += "   ";
		result += "Node (priority: " + std::to_string(getPriority()) + ")";
		for (HandlerList::iterator iter = handlers.begin(); iter != handlers.end(); ++iter)
		{
			result += "\n";
			for (uint16_t i = 0; i < depth; i++) result += "   ";
			TypeInfo t = iter->first;
			result += " - ";
			result += t.get()->name();
		}
		std::list<EventNode*> children = getChildren();
		for (std::list<EventNode*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			result += (*iter)->logHandler(depth + 1);
		}
		return result;
	}
};