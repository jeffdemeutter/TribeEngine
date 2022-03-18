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
	virtual ~EventManager() override;
	EventManager(const EventManager&) = delete;
	EventManager(EventManager&&) noexcept = delete;
	EventManager& operator=(const EventManager&) = delete;
	EventManager& operator=(EventManager&&) noexcept = delete;


	struct EventHandler
	{
		EventType type;
		std::function<void(GameObject*, EventType type)> handle;
	};

	static void Notify(GameObject* go, EventType type);

	static void AddEventHandle(EventType type, const std::function<void(GameObject*, EventType type)>& handle);

private:
	friend class Singleton<EventManager>;
	EventManager() = default;

	std::vector<EventHandler> m_Events;
};

