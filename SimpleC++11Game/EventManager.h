#pragma once
#include "Singleton.h"
#include "Event.h"
#include <cassert>
#include <unordered_map>

class EventManager
	: public Singleton<EventManager>
{
	friend void sendEvent(EventID eventId);

	template <typename T>
	friend void sendEventToHandler(EventID eventId, T* eventHandler);

	friend bool registerEvent(EventID eventId);

	template <typename T>
	friend void attachEvent(EventID eventId, T* eventHandler);

	template <typename T>
	friend void detachEvent(EventID eventId, T* eventHandler);

private:
	using EventMap = std::unordered_map<EventID, Event*>;
	using EventMapIterator = EventMap::iterator;

	EventMap m_eventMap;

	void sendEvent(EventID eventId);

	void sendEventToHandler(EventID eventId, EventHandler& eventHandler);
	bool registerEvent(EventID eventId);

	void attachEvent(EventID eventId, EventHandler& eventHandler);

	void detachEvent(EventID eventId, EventHandler& eventHandler);

public:
	virtual ~EventManager();
};



inline void sendEvent(EventID eventId)
{
	EventManager* pEventManager = EventManager::getSingletonPtr();
	assert(pEventManager);
	if (pEventManager)
	{
		pEventManager->sendEvent(eventId);
	}
}

template <typename T>
inline void sendEventToHandler(EventID eventId, T* eventHandler)
{
	static_assert(std::is_base_of<EventHandler, T>::value, "Class provided is not derived from EventHandler");

	EventManager* pEventManager = EventManager::GetSingletonPtr();
	assert(pEventManager);
	if (pEventManager)
	{
		pEventManager->sendEventToHandler(eventId, *static_cast<EventHandler*>(eventHandler));
	}
}

inline bool registerEvent(EventID eventId)
{
	bool added = false;

	EventManager* pEventManager = EventManager::getSingletonPtr();
	assert(pEventManager);
	if (pEventManager)
	{
		added = pEventManager->registerEvent(eventId);
	}

	return added;
}

template <typename T>
inline void attachEvent(EventID eventId, T* eventHandler)
{
	static_assert(std::is_base_of<EventHandler, T>::value, "Class provided is not derived from EventHandler");

	EventManager* pEventManager = EventManager::getSingletonPtr();
	assert(pEventManager);
	if (pEventManager)
	{
		pEventManager->attachEvent(eventId, *static_cast<EventHandler*>(eventHandler));
	}
}

template <typename T>
inline void detachEvent(EventID eventId, T* eventHandler)
{
	static_assert(std::is_base_of<EventHandler, T>::value, "Class provided is not derived from EventHandler");

	EventManager* pEventManager = EventManager::getSingletonPtr();
	assert(pEventManager);
	if (pEventManager)
	{
		pEventManager->detachEvent(eventId, *static_cast<EventHandler*>(eventHandler));
	}
}
