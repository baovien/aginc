#pragma once
#include "../Core/entityManager.h"
#include <cstdlib>

#ifndef VIETNAMESE_SPACE_PROGRAM_ENEMY_H
#define VIETNAMESE_SPACE_PROGRAM_ENEMY_H
class EnemyObject : public Entity
{
public:
    EnemyObject(float x, float y, float direction);
    void updateEntity(sf::RenderWindow *window);
    virtual void collision(Entity* entity);

private:
    EntityManager* manager;
};

#endif //VIETNAMESE_SPACE_PROGRAM_ENEMY_H