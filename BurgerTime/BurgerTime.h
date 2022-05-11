#pragma once
#include <Tribe.h>
class BurgerTime final : public Tribe
{
public:
	BurgerTime() = default;
	~BurgerTime() override = default;
	BurgerTime(const BurgerTime&) = delete;
	BurgerTime(BurgerTime&&) noexcept = delete;
	BurgerTime& operator=(const BurgerTime&) = delete;
	BurgerTime& operator=(BurgerTime&&) noexcept = delete;

protected:
	virtual void LoadGame() const override;
};

