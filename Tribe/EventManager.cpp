#include "TribePCH.h"
#include "EventManager.h"

void EventManager::Notify(GameObject* go, EventType type)
{
	for (EventHandler& eh : m_Events)
		if (eh.type == type)
			eh.handle(go, type);
}

void EventManager::AddEventHandle(EventType type, const FuncCallBack& handle)
{
	m_Events.push_back({type, handle});
}
