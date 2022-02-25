#include "TribePCH.h"
#include "RenderManager.h"
#include "SceneManager.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "Texture2D.h"

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

void RenderManager::InitImpl()
{
	PrintSDLVersion();

	// init sdl for video usage
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	// create the window
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Width,
		m_Height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // | SDL_WINDOW_ALWAYS_ON_TOP
	);
	if (m_Window == nullptr)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	// create the renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window, 
		GetOpenGLDriverIndex(), 
		SDL_RENDERER_ACCELERATED //| SDL_RENDERER_TARGETTEXTURE
	);
	if (m_Renderer == nullptr) 
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());

	// initialize imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
}

void RenderManager::RenderImpl() const
{
	// clear renderer
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	// render scenes
	SceneManager::Render();
	
	RenderUI();

	SDL_RenderPresent(m_Renderer);
}

void RenderManager::UpdateWindow(int width, int height)
{
	auto& inst = GetInstance();
	inst.m_Width = width;
	inst.m_Height = height;

	SDL_SetWindowSize(inst.m_Window, width, height);
}

void RenderManager::RenderUI() const
{
	// render imgui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();


	// open the first menu on the left
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
	| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	static ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_CentralNode | ImGuiDockNodeFlags_NoTabBar;
	ImGui::Begin("main", NULL, flags);
	{
		// init settings for this window
		ImGui::SetWindowPos({ 0, 0 }); // ensures that the window is alligned to the left
		ImGui::SetWindowSize({ 200 , float(m_Height) });
		
		
		ImGui::End();
	}


	// render other ui elements
	SceneManager::RenderUI();

	// end imgui frame
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

RenderManager::~RenderManager()
{
	// destroy imgui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// cleanup all sdl stuff
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}
