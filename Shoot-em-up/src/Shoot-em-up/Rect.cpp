#include "Rect.h"
#include "SDL.h"

void Rect::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { _x, _y, _width, _height };

	SDL_RenderDrawRect(renderer, &rect);
}