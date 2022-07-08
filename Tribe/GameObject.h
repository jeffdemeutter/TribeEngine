#pragma once

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) noexcept = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) noexcept = delete;



protected:
	friend class Scene;
	void Render() const;
	void Update();
private:

};

