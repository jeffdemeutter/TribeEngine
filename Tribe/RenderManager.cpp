#include "TribePCH.h"
#include "RenderManager.h"
#include "SceneManager.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "SoundManager.h"

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

void RenderManager::Init()
{
	PrintSDLVersion();

	// init sdl for video usage
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	// create the window
	Instance().m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Instance().m_Width,
		Instance().m_Height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // | SDL_WINDOW_ALWAYS_ON_TOP
	);
	if (Instance().m_Window == nullptr)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	// create the renderer
	Instance().m_Renderer = SDL_CreateRenderer(
		Instance().m_Window,
		GetOpenGLDriverIndex(), 
		SDL_RENDERER_ACCELERATED //| SDL_RENDERER_TARGETTEXTURE
	);
	if (Instance().m_Renderer == nullptr)
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());

	// initialize imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Instance().m_Window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

}

void RenderManager::Render()
{
	// clear renderer
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(Instance().m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(Instance().m_Renderer);
	

	// render scenes
	SceneManager::Render();
	
	Instance().RenderUI();

	SDL_RenderPresent(Instance().m_Renderer);
}

void RenderManager::UpdateWindow(int width, int height)
{
	auto& inst = Instance();
	inst.m_Width = width;
	inst.m_Height = height;

	SDL_SetWindowSize(inst.m_Window, width, height);
}

void RenderManager::RenderUI() const
{
	if (!m_RenderImGui)
		return;

	// render imgui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	
	ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

	//ImGui::ShowDemoWindow();
	ImGui::Begin("main");
	{
		ImGui::Text("Enable/Disable ImGui with 'TAB'");
		ImGui::Text("Inputs:");
		ImGui::Text("keyboard - D | Controller - X | plays sound effect");

		ImGui::Separator();
		ImGui::Text("Volume ");
		ImGui::SameLine();
		if (ImGui::Button("+"))
			SoundManager::ChangeVolume(10);
		ImGui::SameLine();
		if (ImGui::Button("-"))
			SoundManager::ChangeVolume(-10);

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
