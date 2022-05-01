#include "TribePCH.h"
#include "ResourceManager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderManager.h"
#include "Texture2D.h"
#include "Font.h"

ResourceManager::~ResourceManager()
{
	for (auto& pTexture : m_pTextures)
		SafeDelete(pTexture.second);
	m_pTextures.clear();

	for (auto& pFont : m_pFonts)
		SafeDelete(pFont.second);
	m_pFonts.clear();
}

void ResourceManager::Init(const std::string& dataPath)
{
	Instance().m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	

	if (TTF_Init() != 0) 
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	
}

Texture2D* ResourceManager::LoadTexture(const std::string& file)
{
	// check if a texture is already loaded in
	if (Instance().m_pTextures.find(file) != Instance().m_pTextures.cend())
		return Instance().m_pTextures.at(file);

	// create new texture and store it
	const auto fullPath = Instance().m_DataPath + file;
	auto pTexture = IMG_LoadTexture(RenderManager::GetSDLRenderer(), fullPath.c_str());
	if (!pTexture) 
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	
	return Instance().m_pTextures[file] = new Texture2D(pTexture);
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const std::string key = file + std::to_string(size);
	// check if a font is already loaded in
	if (Instance().m_pFonts.find(file) != Instance().m_pFonts.cend())
		return Instance().m_pFonts.at(file);

	// create new font and store it
	return Instance().m_pFonts[key] = new Font(Instance().m_DataPath + file, size);
}
