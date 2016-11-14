#ifndef VIETNAMESE_SPACE_PROGRAM_PLAYER_H
#define VIETNAMESE_SPACE_PROGRAM_PLAYER_H

#include "../Core/entityManager.h"
#include "../Core/score.h"
#include "../Core/playerLives.h"
#include "bullet.h"
#include "asteroid.h"
#include "overheat.h"

class Player : public Entity
{
public:
    const double pi = 3.141592;
    float speed=0.0f, maxSpeed=8.0f, dec=0.3f, acc=0.6f, angle = 0.0f, turnspeed=0.14f;
    bool up=0,down=0,left=0,right=0;

    Player(Lives* lives, Score* score, EntityManager* manager, float x, float y, sf::RenderWindow *window, int gamemode);
    void updateEntity(sf::RenderWindow *window);
    virtual void collision(Entity* entity);


private:
    int gamemode;
    Overheat* overheat;
    Lives* lives;
    Score* score;
    EntityManager* manager;
    bool space;

    sf::Texture* texture;
};

#endif //VIETNAMESE_SPACE_PROGRAM_PLAYER_H