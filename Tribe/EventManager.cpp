#include "TribePCH.h"
#include "EventManager.h"

EventManager::~EventManager()
{
	
}

void EventManager::Notify(GameObject* go, EventType type)
{
	auto& inst = Get();

	for (EventHandler& eh : inst.m_Events)
		if (eh.type == type)
			eh.handle(go, type);
}

void EventManager::AddEventHandle(EventType type, const std::function<void(GameObject*, EventType)>& handle)
{
	Get().m_Events.push_back({type, handle});
}
