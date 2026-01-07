#include "TextManager.h"
#include <SDL_ttf.h>
#include <iostream>

TextManager* TextManager::Instance = nullptr;

TextManager::TextManager() {
	Instance = nullptr;
}

TextManager::~TextManager() {
	for (auto font : _fonts) {
		TTF_CloseFont(font.second);
	}

	delete Instance;
}

TTF_Font* TextManager::OpenFont(std::string fontPath, int fontSize) {
	const char* path = fontPath.c_str();

	auto it = _fonts.find(path);

	if (it != _fonts.end()) {
		return it->second;
	}

	TTF_Font* font = TTF_OpenFont(path, fontSize);

	if (font == NULL) {
		std::cout << "Specified path not found." << std::endl;
		exit(1);
	}

	_fonts[path] = font;

	return font;
}