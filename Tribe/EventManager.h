#pragma once
#include <functional>

#include "GameObject.h"
#include "Singleton.h"

enum EventType
{
	PlayerDied,
	TookDamage,
	EnemyDied,
	BurgerDrop
};


class GameObject;
class EventManager : public Singleton<EventManager>
{
public:
	~EventManager() override;

	struct EventHandler
	{
		EventType type;
		std::function<void(GameObject*, EventType type)> handle;
	};

	static void Notify(GameObject* go, EventType type);

	static void AddEventHandle(EventType type, const std::function<void(GameObject*, EventType)>& handle);

private:
	friend class Singleton<EventManager>;
	EventManager() = default;

	std::vector<EventHandler> m_Events;
};

