#pragma once
#include "Enemy.h"

class ReturnEnemy :
    public Enemy
{
private:
    

public:
    ReturnEnemy(Geometry* body, Collider* collider) :
        Enemy(body, collider, 500, 5, 400, 1) {}

    ~ReturnEnemy() {}

    void Spawn(float deltaTime) override;

    void Shoot() override;
};

