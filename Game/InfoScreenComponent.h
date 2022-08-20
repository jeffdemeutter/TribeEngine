#pragma once
#include <Component.h>
class InfoScreenComponent : public Component
{
public:
	InfoScreenComponent(GameObject* pGo, float time, const std::string& sceneToLoad);
	~InfoScreenComponent() override = default;
	
	void Update(GameContext&) override;
	void Render() const override {}

private:
	float m_MaxTime;
	float m_CurrentTime;

	std::string m_SceneToLoad;
};

