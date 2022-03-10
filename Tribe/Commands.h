#pragma once
#include <functional>

class Command final
{
public:
	Command(std::function<void()> func);
	~Command() = default;
	void Execute() const { m_Execute(); }

private:
	std::function<void()> m_Execute;
};

