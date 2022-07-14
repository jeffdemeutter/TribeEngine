#pragma once
#include "Component.h"

class PrinterComponent final : public Component
{
public:
	PrinterComponent(GameObject* go, const std::string& text)
		: Component(go)
		, m_Text(text)
	{
	}
	virtual ~PrinterComponent() override = default;

	virtual void Update(GameContext& ) override {}
	virtual void Render() const override {}

	void SetText(const std::string& text) { m_Text = text; }
	void Print() const;

private:
	std::string m_Text = "default";
};
