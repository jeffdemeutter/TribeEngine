#pragma once
#include <functional>

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
	
	using FuncCallBack = std::function<void(GameObject*, int)>;
	struct EventHandler
	{
		int type;
		FuncCallBack handle;
	};

	void Notify(GameObject* go, int type);

	void AddEventHandle(int type, const FuncCallBack& handle);

private:
	std::vector<EventHandler> m_Events;
};

