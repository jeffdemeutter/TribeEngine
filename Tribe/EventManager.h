#pragma once
#include <functional>

#include "GameObject.h"

enum EventType
{
	All,
	PlayerDied,
	TookDamage,
	EnemyDied,
	BurgerDrop
};

class GameObject;
class EventManager final
{
public:
	EventManager() = default;
	~EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager(EventManager&&) noexcept = delete;
	EventManager& operator=(const EventManager&) = delete;
	EventManager& operator=(EventManager&&) noexcept = delete;

	using FuncCallBack = std::function<void(GameObject*, EventType)>;

	struct EventHandler
	{
		EventType type;
		FuncCallBack handle;
	};

	void Notify(GameObject* go, EventType type);

	void AddEventHandle(EventType type, const FuncCallBack& handle);

private:
	std::vector<EventHandler> m_Events;
};

