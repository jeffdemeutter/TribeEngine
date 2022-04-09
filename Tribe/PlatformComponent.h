#pragma once
#include "BaseComponent.h"
class PlatformComponent : public Component
{
public:
	PlatformComponent(GameObject* go);
	~PlatformComponent() override = default;

	// Inherited via Component
	virtual void Update() override;
	virtual void Render() const override;

private:
	int m_Height = 0;
};

