#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "GameManager.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL::Init Error : " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Shoot_em_up", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "SDL::CreateWindow Error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, NULL);
    if (renderer == NULL)
    {
        std::cout << "SDL::CreateRenderer Error : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0)
    {
        std::cout << "Error TTF_Init : " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Error Mix_OpenAudio" << std::endl;
    }

    GameManager::Get()->Init(renderer);
    GameManager::Get()->Launch();
    GameManager::Get()->Shutdown();

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}