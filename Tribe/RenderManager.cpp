#include "TribePCH.h"
#include "RenderManager.h"

#include "GameObject.h"
#include "Scene.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}


//====================================

void RenderManager::Init()
{
	auto& inst = Instance();

	PrintSDLVersion();

	// init sdl for video usage
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	// create the window
	inst.m_pWindow = SDL_CreateWindow(
		"Prog 4 exam",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		inst.m_Width,
		inst.m_Height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // | SDL_WINDOW_ALWAYS_ON_TOP
	);
	if (!inst.m_pWindow)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	// create the renderer
	inst.m_pRenderer = SDL_CreateRenderer(
		inst.m_pWindow,
		GetOpenGLDriverIndex(),
		SDL_RENDERER_ACCELERATED //| SDL_RENDERER_TARGETTEXTURE
	);
	if (!inst.m_pRenderer)
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
}

void RenderManager::Render(std::shared_ptr<Scene> pScene, const std::vector<GameObject*>& persistentObjects)
{
	auto& inst = Instance();
	// clear renderer
	SDL_SetRenderDrawColor(inst.m_pRenderer, inst.m_ClearColor.r, inst.m_ClearColor.g, inst.m_ClearColor.b, inst.m_ClearColor.a);
	SDL_RenderClear(inst.m_pRenderer);

	// render scenes
	pScene->Render();

	for (const GameObject* pObject : persistentObjects)
		pObject->Render();

	SDL_RenderPresent(inst.m_pRenderer);
}

void RenderManager::Destroy()
{
	auto& inst = Instance();

	// cleanup all sdl stuff
	if (!inst.m_pRenderer)
	{
		SDL_DestroyRenderer(inst.m_pRenderer);
		inst.m_pRenderer = nullptr;
	}
	SDL_DestroyWindow(inst.m_pWindow);
	inst.m_pWindow = nullptr;
	SDL_Quit();
}

void RenderManager::SetBackgroundColor(const glm::vec3& color)
{
	Instance().m_ClearColor.r = Uint8(color.x * 255.f);
	Instance().m_ClearColor.g = Uint8(color.y * 255.f);
	Instance().m_ClearColor.b = Uint8(color.z * 255.f);
}

void RenderManager::UpdateWindow(int width, int height)
{
	auto& inst = Instance();

	inst.m_Width = width;
	inst.m_Height = height;

	SDL_SetWindowSize(inst.m_pWindow, width, height);
}
