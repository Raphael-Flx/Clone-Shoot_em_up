#pragma once
#include "Enemy.h"

class Geometry;
class Collider;

#define PATTERN_TIME 2

class Boss :
    public Enemy
{
private:
    enum class Pattern {
        MoveForward,
        Nothing, // TODO
        MultipleShoot,
        GuidedShoot,

    };

    float _lastPatternTime = 0.f;

    Pattern _currentPattern = Pattern::MoveForward;

public:
    Boss(Geometry* body, Collider* collider) :
        Enemy(body, collider, 100000, 750, 125, 1) {}

    void Update(float deltaTime) override;

    void Spawn(float deltaTime) override;

    void Shoot() override;

    void ChooseRandomPattern();

    void MoveForward();

    void ChooseDirection();

    void MultipleShoot();

    void GuidedShoot();
};

