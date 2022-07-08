#include "TribePCH.h"
#include "RenderManager.h"

#include "Scene.h"

class RenderManager::SDLRendererImpl
{
public:
	SDLRendererImpl();
	~SDLRendererImpl();
	SDLRendererImpl(const SDLRendererImpl&) = delete;
	SDLRendererImpl(SDLRendererImpl&&) noexcept = delete;
	SDLRendererImpl& operator=(const SDLRendererImpl&) = delete;
	SDLRendererImpl& operator=(SDLRendererImpl&&) noexcept = delete;
	
	void Render(std::shared_ptr<Scene> pScene) const;

	SDL_Renderer* GetSDLRenderer() const {
		return m_pRenderer;
	}
	SDL_Rect GetWindowRect() const {
		return { 0, 0, m_Width, m_Height };
	}
	void SetBackgroundColor(const SDL_Color& color) {
		m_ClearColor = color;
	}

	void UpdateWindow(int width, int height);

private:
	int m_Width = 900;
	int m_Height = 600;
	SDL_Renderer* m_pRenderer{};
	SDL_Window* m_pWindow{};
	SDL_Color m_ClearColor{};
};

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

RenderManager::SDLRendererImpl::SDLRendererImpl()
{
	PrintSDLVersion();

	// init sdl for video usage
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	// create the window
	m_pWindow = SDL_CreateWindow(
		"something",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Width,
		m_Height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // | SDL_WINDOW_ALWAYS_ON_TOP
	);
	if (!m_pWindow)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	// create the renderer
	m_pRenderer = SDL_CreateRenderer(
		m_pWindow,
		GetOpenGLDriverIndex(),
		SDL_RENDERER_ACCELERATED //| SDL_RENDERER_TARGETTEXTURE
	);
	if (!m_pRenderer)
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
}

RenderManager::SDLRendererImpl::~SDLRendererImpl()
{
	// cleanup all sdl stuff
	if (!m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void RenderManager::SDLRendererImpl::Render(std::shared_ptr<Scene> pScene) const
{
	// clear renderer
	SDL_SetRenderDrawColor(m_pRenderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
	SDL_RenderClear(m_pRenderer);

	// render scenes
	pScene->Render();

	SDL_RenderPresent(m_pRenderer);
}

void RenderManager::SDLRendererImpl::UpdateWindow(int width, int height)
{
	m_Width = width;
	m_Height = height;

	SDL_SetWindowSize(m_pWindow, width, height);
}

void RenderManager::Init()
{
	Instance().m_pImpl = std::make_unique<SDLRendererImpl>();
}

void RenderManager::Render(std::shared_ptr<Scene> pScene)
{
	Instance().m_pImpl->Render(pScene);
}

void RenderManager::Destroy()
{
	Instance().m_pImpl.reset();
}

SDL_Renderer* RenderManager::GetSDLRenderer()
{
	return Instance().m_pImpl->GetSDLRenderer();
}

SDL_Rect RenderManager::GetWindowRect()
{
	return Instance().m_pImpl->GetWindowRect();
}

void RenderManager::SetBackgroundColor(const SDL_Color& color)
{
	Instance().m_pImpl->SetBackgroundColor(color);
}

void RenderManager::UpdateWindow(int width, int height)
{
	Instance().m_pImpl->UpdateWindow(width, height);
}
