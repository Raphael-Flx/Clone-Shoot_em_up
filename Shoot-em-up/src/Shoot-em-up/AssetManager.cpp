#include "AssetManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

AssetManager* AssetManager::Instance = nullptr;

AssetManager::AssetManager() {
    Instance = nullptr;
}

AssetManager::~AssetManager() {
    for (int i = 0; i < _paths.size(); ++i) {
        SDL_DestroyTexture(_paths.begin()->second);
    }

    _paths.clear();

    delete Instance;
}

SDL_Texture* AssetManager::LoadTexture(SDL_Renderer* renderer, const char* path) {

    auto it = _paths.find(path);

    if (it != _paths.end())
        return it->second;

    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        std::cout << "Couldn't load texture." << std::endl;
    }

    _paths[path] = texture;

    return texture;
}