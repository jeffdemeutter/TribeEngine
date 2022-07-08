#pragma once


class Scene
{
public:


	void Update();


private:
	friend class RenderManager;
	void Render();
};

