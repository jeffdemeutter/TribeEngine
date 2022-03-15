#pragma once
#include "BaseComponent.h"

class TextComponent;
class RemainingLivesComponent : public Component
{
public:
	RemainingLivesComponent(GameObject* go, TextComponent* pText);
	~RemainingLivesComponent() override = default;
	RemainingLivesComponent(const RemainingLivesComponent&) = delete;
	RemainingLivesComponent(RemainingLivesComponent&&) noexcept = delete;
	RemainingLivesComponent& operator=(const RemainingLivesComponent&) = delete;
	RemainingLivesComponent& operator=(RemainingLivesComponent&&) noexcept = delete;

	void UpdateLives(GameObject* go);

	virtual void Update() override {};
	virtual void Render() const override {};

private:
	TextComponent* m_pTextComponent = nullptr;
	std::string m_Prefix = "Lives: ";
};
