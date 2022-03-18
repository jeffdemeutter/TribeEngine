#include "TribePCH.h"
#include "EventManager.h"

EventManager::~EventManager()
{
	
}

void EventManager::Notify(GameObject* go, EventType type)
{
	auto& inst = GetInstance();

	for (EventHandler& eh : inst.m_Events)
	{
		if (eh.type == type)
			eh.handle(go, type);
	}
}

void EventManager::AddEventHandle(EventType type, const std::function<void(GameObject*, EventType type)>& handle)
{
	GetInstance().m_Events.push_back({type, handle});
}
