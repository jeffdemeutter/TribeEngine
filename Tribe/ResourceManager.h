#pragma once
#include "Singleton.h"
#include <unordered_map>

class Texture2D;
class Font;
class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager() override;

	// calls to implicit function
	static void Init(const std::string& data);
	static Texture2D* LoadTexture(const std::string& file);
	static Font* LoadFont(const std::string& file, unsigned int size);

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;


	std::string m_DataPath;
	std::unordered_map<std::string, Texture2D*> m_pTextures;
	std::unordered_map<std::string, Font*	  >	m_pFonts;
};

