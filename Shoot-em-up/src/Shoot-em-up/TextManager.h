#pragma once
#include <string>
#include <map>

struct SDL_Renderer;
struct TTF_Font;
struct SDL_Color;

class TextManager
{
private:
	std::map<const char*, TTF_Font*> _fonts;

	static TextManager* Instance;

	TextManager();
	~TextManager();

public:
	static TextManager* Get()
	{
		if (Instance == nullptr)
		{
			Instance = new TextManager;
		}

		return Instance;
	}

	TTF_Font* OpenFont(std::string fontPath, int fontSize);
};