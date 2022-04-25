#pragma once

template <typename T>
class Singleton
{
public:
	virtual ~Singleton() = default;

protected:
	static T& Get()
	{
		static T instance{};
		return instance;
	}
	Singleton() = default;
	Singleton(const Singleton& other) = delete;
	Singleton(Singleton&& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;
	Singleton& operator=(Singleton&& other) = delete;
};
