#pragma once
#include "BaseComponent.h"

class PlateauComponent final : public Component
{
public:
	PlateauComponent() = default;
	virtual ~PlateauComponent() override = default;
	PlateauComponent(const PlateauComponent&) = delete;
	PlateauComponent(PlateauComponent&&) noexcept = delete;
	PlateauComponent& operator=(const PlateauComponent&) = delete;
	PlateauComponent& operator=(PlateauComponent&&) noexcept = delete;



private:

};

