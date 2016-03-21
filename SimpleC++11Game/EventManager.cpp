#include "stdafx.h"
#include "EventManager.h"



EventManager::~EventManager()
{

	for (EventMapIterator iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter)
	{
		Event* pEvent = iter->second;
		if (pEvent != nullptr) 
		{
			delete pEvent;
			iter->second = nullptr;
		}
		m_eventMap.clear();
	}

}


void EventManager::sendEvent(EventID eventId)
{
	EventMapIterator result = m_eventMap.find(eventId);
	if (result != m_eventMap.end())
	{
		assert(result->second);
		if (result->second)
		{
			result->second->send();
		}
	}
}

void EventManager::sendEventToHandler(EventID eventId, EventHandler& eventHandler)
{
	EventMapIterator result = m_eventMap.find(eventId);
	if (result != m_eventMap.end())
	{
		assert(result->second);
		if (result->second)
		{
			result->second->sendToHandler(eventHandler);
		}
	}
}

bool EventManager::registerEvent(EventID eventId)
{
	bool added = false;

	EventMapIterator result = m_eventMap.find(eventId);
	if (result == m_eventMap.end())
	{
		Event* pNewEvent = new Event(eventId);

		if (pNewEvent)
		{
			std::pair<EventID, Event*> newEvent(eventId, pNewEvent);
			auto addedIter = m_eventMap.insert(newEvent);
			added = addedIter.second;
		}
	}

	assert(added);
	return added;
}

void EventManager::attachEvent(EventID eventId, EventHandler& eventHandler)
{
	EventMapIterator result = m_eventMap.find(eventId);
	assert(result != m_eventMap.end());
	if (result != m_eventMap.end())
	{
		assert(result->second);
		result->second->attachListener(eventHandler);
	}
}

void EventManager::detachEvent(EventID eventId, EventHandler& eventHandler)
{
	EventMapIterator result = m_eventMap.find(eventId);
	assert(result != m_eventMap.end());
	if (result != m_eventMap.end())
	{
		assert(result->second);
		result->second->detachListener(eventHandler);
	}
}

