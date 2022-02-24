#include "EventNode.h"

namespace Poly {
	void EventNode::dispatch(Event* e) {
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
}