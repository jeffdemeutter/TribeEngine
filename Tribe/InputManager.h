#pragma once
#include <XInput.h>
#include "Singleton.h"

enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY
};

class InputManager final : public Singleton<InputManager>
{
public:
	static bool ProcessInput() { return GetInstance().ProcessInputImpl(); }
	static bool IsPressed(ControllerButton button) { GetInstance().IsPressedImpl(button); }

private:
	friend class Singleton<InputManager>;
	InputManager() = default;


	XINPUT_STATE m_CurrentState{};

	
	bool ProcessInputImpl();
	bool IsPressedImpl(ControllerButton button) const;
};


