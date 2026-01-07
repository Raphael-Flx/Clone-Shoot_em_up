#pragma once
#include "Geometry.h"

#include <string>

struct TTF_Font;
struct SDL_Renderer;
struct SDL_Color;

class Text :
	public Geometry
{
private:
	SDL_Surface* _textSurface = nullptr;
	SDL_Texture* _textTexture = nullptr;
	TTF_Font* _font;
	SDL_Color _color;

	const char* _text;
public:
	Text(SDL_Renderer* renderer, const char* font, int fontSize, const char* text, int width, int height, SDL_Color color = { 255, 255, 255, 255 });
	~Text();

	void SetColor(SDL_Renderer* renderer, SDL_Color color);
	void SetText(SDL_Renderer* renderer, const char* text);
	void SetFont(SDL_Renderer* renderer, TTF_Font* font);

	void Draw(SDL_Renderer* renderer) override;
};

