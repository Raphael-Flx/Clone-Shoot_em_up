#pragma once
#include <map>

struct SDL_Texture;
struct SDL_Renderer;

class AssetManager
{
private:
    std::map<const char*, SDL_Texture*> _paths;

    static AssetManager* Instance;

    AssetManager();
    ~AssetManager();

public:
    static AssetManager* Get() {
        if (Instance == nullptr) {
            Instance = new AssetManager;
        }

        return Instance;
    }

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path);
};