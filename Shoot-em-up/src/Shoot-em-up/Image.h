#pragma once
#include "Geometry.h"

struct SDL_Renderer;
struct SDL_Texture;

class Image : public Geometry
{
private:
    SDL_Texture* _texture;

    const char* _path = "";
public:
    Image(int width, int height, SDL_Renderer* renderer, const char* path);

    ~Image() {}

    void Draw(SDL_Renderer* renderer) override;

    void Resize(int width, int height) override;

    void SetPath(SDL_Renderer* renderer, const char* path);
};