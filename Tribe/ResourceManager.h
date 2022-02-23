#pragma once
#include "Singleton.h"
#include <unordered_map>

class Texture2D;
class Font;
class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager();

	// calls to implicit function
	static void Init(const std::string& data) { GetInstance().InitImpl(data); }
	static Texture2D* LoadTexture(const std::string& file) { return GetInstance().LoadTextureImpl(file); }
	static Font* LoadFont(const std::string& file, unsigned int size) { return GetInstance().LoadFontImpl(file, size); }

	

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	// variables
	std::string m_DataPath;
	std::unordered_map<std::string, Texture2D*> m_pTextures;
	std::unordered_map<std::string, Font*	  >	m_pFonts;


	// implemented functions, these correspond to the static functions which are public
	void InitImpl(const std::string& data);
	Texture2D* LoadTextureImpl(const std::string& file);
	Font* LoadFontImpl(const std::string& file, unsigned int size);
};

