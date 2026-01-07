#pragma once
#include "Enemy.h"
#include "CircleCollider.h"

class ForwardEnemy :
    public Enemy
{
private:

public:
    ForwardEnemy(Geometry* body, Collider* collider) :
        Enemy(body, collider, 300, 10, 350, 0.5) {}

    ~ForwardEnemy() {}

    void Spawn(float deltaTime) override;
    void Shoot() override;
};

