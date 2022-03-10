#pragma once
#include <functional>

class Command final
{
public:
	Command(std::function<void()> func) 
		: m_Execute{ func }
	{
	}

	~Command() = default;

	void Execute() const { m_Execute(); }

private:
	std::function<void()> m_Execute;
};

