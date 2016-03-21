#pragma once

#include <vector>

using EventID = int32_t;

class EventHandler;

class Event
{

public:
	explicit Event( EventID eventId);
	void send();
	void sendToHandler(EventHandler& eventHandler);
	void attachListener(EventHandler& evenHandler);
	void detachListener(EventHandler& eventHandler);

	~Event();

private:
	using EventHandlerList = std::vector<EventHandler*>;
	using EventHandlerListIterator = EventHandlerList::iterator;

	EventHandlerList m_listeners;
	EventID m_id;

};

