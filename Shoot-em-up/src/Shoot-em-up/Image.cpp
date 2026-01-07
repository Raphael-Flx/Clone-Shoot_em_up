#include "Image.h"
#include "Geometry.h"
#include "SDL_image.h"
#include "AssetManager.h"

#include <iostream>

Image::Image(int width, int height, SDL_Renderer* renderer, const char* path) :
    Geometry(width, height), _path(path)

{
    _texture = AssetManager::Get()->LoadTexture(renderer, _path);
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}

void Image::Draw(SDL_Renderer* renderer) {
    SDL_Rect destRect{ _x, _y, _width, _height };
    SDL_RenderCopy(renderer, _texture, 0, &destRect);
}

void Image::Resize(int width, int height) {
    float factorWidth = width / (float) _width;
    float factorHeight = height / (float) _height;

    float factorMin = std::min(factorWidth, factorHeight);

    if (width == -1)
        factorMin = factorHeight;


    if (height == -1)
        factorMin = factorWidth;

    _width *= factorMin;
    _height *= factorMin;
}

void Image::SetPath(SDL_Renderer* renderer, const char* path)
{
    _path = path;

    _texture = AssetManager::Get()->LoadTexture(renderer, _path);
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}