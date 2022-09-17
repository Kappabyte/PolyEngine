//
// Created by avery on 2022-09-15.
//

#include "EventNodeBase.h"

namespace Poly {

    bool IEventNode::dispatch(TypeInfo info, Poly::Event *event) {
        bool propagateResult = true;
        dispatch(info, event, propagateResult, this);
    }

    bool IEventNode::dispatch(TypeInfo info, Event* event, bool &propagateResult, IEventNode* root) {
        //Try to handle the event in a local handler first
        auto it = listeners.find(info);
        if (it != listeners.end()) {
            //Go through each registered handler and execute it, cancelling if the event was cancelled
            auto iter = it->second->begin();
            while (iter != it->second->end()) {
                auto* listener = static_cast<EventListener<Event>*>(iter->second);
                listener->handle(event);
                if(event->isCancelled()) {
                    if(propagateResult) {
                        root->dispatchResult(info, event, propagateResult);
                        propagateResult = false;
                    }
                    return true;
                }
                iter++;
            }
        }

        auto children = getEventNodeChildren();

        auto iterator = children.begin();
        while(iterator != children.end()) {
            iterator->second->dispatch(info, event, propagateResult, root);
            if(event->isCancelled()) {
                if(propagateResult) {
                    root->dispatchResult(info, event, propagateResult);
                    propagateResult = false;
                }
                return true;
            }
            iterator++;
        }

        if(propagateResult) {
            root->dispatchResult(info, event, propagateResult);
            propagateResult = false;
        }
        return true;
    }

    void IEventNode::dispatchResult(TypeInfo info, Event* event, bool& propagateResult) {
        //Try to handle the event in a local handler first
        auto it = resultListeners.find(info);
        if (it != resultListeners.end()) {
            //Go through each registered handler and execute it, cancelling if the event was cancelled
            auto iter = it->second->begin();
            while (iter != it->second->end()) {
                auto* listener = static_cast<EventResultListener<Event>*>(iter->second);
                listener->handleResult(event, propagateResult);
                if(!propagateResult) return;
                iter++;
            }
        }

        auto children = getEventNodeChildren();

        auto iterator = children.begin();
        while(iterator != children.end()) {
            iterator->second->dispatchResult(info, event, propagateResult);
            if(!propagateResult) return;
            iterator++;
        }
    }
}
