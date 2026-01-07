#pragma once
#include "Entity.h"
#include "Image.h"

struct SDL_Renderer;
struct SDL_Texture;

class Parallax : public Entity
{
private:
    Entity* _cloneImage;
    float _speed;

public:
    Parallax(int width, int height, SDL_Renderer* renderer, const char* path, float speed = 1) :
        Entity(new Image(width, height, renderer, path)), _speed(speed)
    {
        _cloneImage = new Entity(new Image(width, height, renderer, path));
        _cloneImage->SetPosition(_body->GetWidth(), 0, 0, 0);
    }

    ~Parallax() {}

    void Draw(SDL_Renderer* renderer) override;

    void Resize(int width, int height) override;

    void Update(float deltaTime) override;

    void Move(float x, float y);
};