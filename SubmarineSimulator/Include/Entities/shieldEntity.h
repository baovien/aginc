#ifndef SUBMARINESIMULATORSHIELDPOWERUP_H
#define SUBMARINESIMULATORSHIELDPOWERUP_H

#include "../Core/entityManager.h"
#include "../Core/entity.h"
#include "../Core/audioLoader.h"
#include "../Core/pauseableClock.h"
#include "../Core/machine.h"
#include "player.h"

class ShieldEntity : public Entity
{
public:
    ShieldEntity(sf::RenderWindow* window, Player* player, AudioLoader* audioLoader);
    void updateEntity(sf::RenderWindow *window);
    virtual void collision(Entity* entity);
private:
    sfuser::PauseableClock clock; // starter clocken
    Player* player = nullptr;

    AudioLoader* audioLoader = nullptr;
public:
    bool* isShieldActivePointer = nullptr;

};
#endif //SUBMARINESIMULATORSHIELDPOWERUP_H
