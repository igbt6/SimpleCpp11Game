#include "stdafx.h"
#include "Event.h"
#include "EventHandler.h"


Event::Event(EventID eventId):m_id(eventId)
{
}


void Event::send() 
{
	for (auto& listener : m_listeners)
	{
		if (listener != nullptr) 
		{
			listener->handleEvent(this);
		}
	}
}

void Event::sendToHandler(EventHandler& eventHandler)
{
	auto found = std::find(m_listeners.begin(), m_listeners.end(), &eventHandler);
	if (found != m_listeners.end())
	{
		(*found)->handleEvent(this);
	}

}



void Event::attachListener(EventHandler& eventHandler)
{
	m_listeners.push_back(&eventHandler);
}



void Event::detachListener(EventHandler& eventHandler)
{
	for (EventHandlerListIterator iter = m_listeners.begin();
	iter != m_listeners.end();
		++iter)
	{
		if (&eventHandler == *iter)
		{
			m_listeners.erase(iter);
			break;
		}
	}
}



Event::~Event()
{
}
