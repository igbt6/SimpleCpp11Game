#pragma once

#include <cassert>
#include <vector>

template <typename Observer>
class Notifier
{
private:
	using Observers = std::vector<Observer*>;
	Observers m_observers;

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	template <void(Observer::*Method)()>
	void notify();
};

template <typename Observer>
void Notifier<Observer>::addObserver(Observer* observer)
{
	assert(find(m_observers.begin(), m_observers.end(), observer) == m_observers.end());
	m_observers.emplace_back(observer);
}

template <typename Observer>
void Notifier<Observer>::removeObserver(Observer* observer)
{
	auto object = find(m_observers.begin(), m_observers.end(), observer);
	if (object != m_observers.end())
	{
		m_observers.erase(object);
	}
}

template <typename Observer>
template <void(Observer::*Method)()>
void Notifier<Observer>::notify()
{
	for (auto& observer : m_observers)
	{
		(observer->*Method)();
	}
}