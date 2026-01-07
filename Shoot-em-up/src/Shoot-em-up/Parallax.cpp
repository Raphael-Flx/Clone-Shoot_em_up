#include "Parallax.h"
#include "Geometry.h"
#include "SDL_image.h"

#include <iostream>

void Parallax::Draw(SDL_Renderer* renderer) {
    _body->Draw(renderer);
    _cloneImage->Draw(renderer);
}

void Parallax::Resize(int width, int height) {
    _body->Resize(width, height);
    _cloneImage->Resize(width, height);

    _cloneImage->SetPosition(_body->GetWidth(), 0, 0, 0);
}

void Parallax::Update(float deltaTime) {
    Vector2f position = GetPosition(1);
    Vector2f clonePosition = _cloneImage->GetPosition(1);

    if (position.x <= 0)
    {
        SetPosition(_body->GetWidth() + position.x, 0, 0, 0);
    }
    if (clonePosition.x <= 0)
    {
        _cloneImage->SetPosition(_body->GetWidth() + clonePosition.x, 0, 0, 0);
    }

    Vector2f translation;

    translation.x = _moveDirection.x * _speed * deltaTime;
    translation.y = 0;

    Move(translation.x, translation.y);
}

void Parallax::Move(float x, float y)
{
    Vector2f position = GetPosition();
    SetPosition(position.x + x, position.y + y);

    Vector2f clonePosition = _cloneImage->GetPosition();
    _cloneImage->SetPosition(clonePosition.x + x, clonePosition.y + y);
}