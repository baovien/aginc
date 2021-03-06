#ifndef SUBMARINESIMULATORPLAYER_H
#define SUBMARINESIMULATORPLAYER_H
#include "../Core/entityManager.h"
#include "../Core/score.h"
#include "../Core/playerLives.h"
#include "dynamicBar.h"
#include "bullet.h"
#include "indestructableObject.h"
#include "../Core/audioLoader.h"
#include "../Core/pauseableClock.h"
#include "../Core/machine.h"


class Player : public Entity
{
public:
    const double pi = 3.141592;
    float speed=0.0f, maxSpeed=400, dec=30.0f, acc=60.0f, angle = 0.0f, turnspeed=7.0f;
    bool up=0,down=0,left=0,right=0;
    Player(std::map<const std::string, std::pair<std::string, int>>* keybindMap,Lives* lives, Score* score, EntityManager* manager, float x, float y, sf::RenderWindow *window, int gamemode, int fighter, AudioLoader* audioLoader);
    void updateEntity(sf::RenderWindow *window);
    virtual void collision(Entity* entity);
private:
    int gamemode;
    int fighter;
    float overheatValue;
    bool space;
    bool isShieldActive = false;
    bool firstTimeLoading = true;
    sfuser::PauseableClock clock;

    AudioLoader* audioLoader = nullptr;
    Lives* lives = nullptr;
    Score* score = nullptr;
    Bar* bar = nullptr;
    EntityManager* manager = nullptr;
    std::map<const std::string, std::pair<std::string, int>> keybindMap;
public:
    bool* isShieldActivePointer = &isShieldActive;
    void pauseClock(bool pause);
};

#endif //SUBMARINESIMULATORPLAYER_H
