#pragma once


class Event;

class EventHandler
{

public: 
	virtual void handleEvent(const Event* event) = 0;

};