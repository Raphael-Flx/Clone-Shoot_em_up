#include "Text.h"
#include "TextManager.h"
#include <SDL.h>
#include <SDL_ttf.h>

Text::Text(SDL_Renderer* renderer, const char* fontPath, int fontSize, const char* text, int width, int height, SDL_Color color) :
	Geometry(width, height)
{
	_text = text;
	_font = TextManager::Get()->OpenFont(fontPath, fontSize);
	_color = color;
}

Text::~Text()
{
	SDL_FreeSurface(_textSurface);
	SDL_DestroyTexture(_textTexture);
}

void Text::Draw(SDL_Renderer* renderer)
{

	if (_textSurface == nullptr)
	{
		_textSurface = TTF_RenderText_Blended(_font, _text, _color);
	}
	if (_textTexture == nullptr)
	{
		_textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
	}

	SDL_QueryTexture(_textTexture, NULL, NULL, &_width, &_height);
	SDL_Rect textRect = { _x, _y, _width, _height };

	SDL_RenderCopy(renderer, _textTexture, NULL, &textRect);
}

void Text::SetColor(SDL_Renderer* renderer, SDL_Color color) 
{
	SDL_FreeSurface(_textSurface);
	SDL_DestroyTexture(_textTexture);

	_textSurface = nullptr;
	_textTexture = nullptr;

	_color = color;

	_textSurface = TTF_RenderText_Blended(_font, _text, _color);
	_textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
}

void Text::SetText(SDL_Renderer* renderer, const char* text) 
{
	SDL_FreeSurface(_textSurface);
	SDL_DestroyTexture(_textTexture);

	_textSurface = nullptr;
	_textTexture = nullptr;

	_text = text;

	_textSurface = TTF_RenderText_Blended(_font, _text, _color);
	_textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
}

void Text::SetFont(SDL_Renderer* renderer, TTF_Font* font) 
{
	SDL_FreeSurface(_textSurface);
	SDL_DestroyTexture(_textTexture);

	_textSurface = nullptr;
	_textTexture = nullptr;

	_font = font;

	_textSurface = TTF_RenderText_Blended(_font, _text, _color);
	_textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
}