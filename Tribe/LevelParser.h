#pragma once


class LevelParser
{
public:
	//static const std::vector<std::vector<glm::vec2>>& ParseFile(const std::string& filePath);

private:
	LevelParser() = delete;
	~LevelParser() = delete;
	LevelParser(const LevelParser&) = delete;
	LevelParser(LevelParser&&) noexcept = delete;
	LevelParser& operator=(const LevelParser&) = delete;
	LevelParser& operator=(LevelParser&&) noexcept = delete;
};
