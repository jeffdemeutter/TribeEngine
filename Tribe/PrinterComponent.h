#pragma once
#include "BaseComponent.h"

class PrinterComponent final : public Component
{
public:
	PrinterComponent(GameObject* go, const std::string& action)
		: Component(go)
		, m_Action(action)
	{
	}
	virtual ~PrinterComponent() override = default;
	virtual void Update() override {}
	virtual void Render() const override {}

	void Print() const;

private:
	std::string m_Action = "default";
};
