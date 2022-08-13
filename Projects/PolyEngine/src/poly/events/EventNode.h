#pragma once
#include "Event.h"
#include <unordered_map>
#include <list>
#include <algorithm>
#include "EventHandler.h"

#include <iostream>

//TODO: Clean up this file!
namespace Poly {
	class EventNode {
	public:
		EventNode(uint32_t priority) : priority(priority) {}
		EventNode() : priority(0) {}

		template<class T, class EventType>
		inline void subscribe(T* executor, void (T::* handler)(EventType*)) {
			if (handlers.find(TypeInfo(&typeid(EventType))) == handlers.end()) {
				handlers.insert({ TypeInfo(&typeid(EventType)), new std::vector<HandlerFunctionBase*> });
			}

			auto eventHandlers = handlers.find(TypeInfo(&typeid(EventType)))->second;
			eventHandlers->push_back(new MemberFunctionHandler<T, EventType>(executor, handler));
		}

		void dispatch(Event* e);

		inline void addChild(EventNode* node) {
			children.insert(std::lower_bound(children.begin(), children.end(), node, [](const EventNode* c, const EventNode* id) {
				return c->getPriority() > id->getPriority();
			}), node);
		}

		virtual inline uint16_t getPriority() const {
			return priority;
		}

		virtual inline std::list<EventNode*> getChildren() {
			return children;
		}

		void logHandler() {
			uint16_t depth = 0;

			printf(logHandler(depth).c_str());
		}
	private:
		typedef std::unordered_map<TypeInfo, std::vector<HandlerFunctionBase*>*, TypeInfo::HashFunction> HandlerList;
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
}