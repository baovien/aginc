#ifndef VIETNAMESE_SPACE_PROGRAM_DYNAMICBAR_H
#define VIETNAMESE_SPACE_PROGRAM_DYNAMICBAR_H
#include "../Core/entityManager.h"
class Bar : public Entity
{
public:
    Bar(sf::RenderWindow *window);
    Bar(sf::RenderWindow* window, float x, float y,float bossHP);
    void updateEntity(sf::RenderWindow *window, float overHeatValue);
    void updateEntity2(sf::RenderWindow* window, float overHeatValue, float x, float y);

protected:
    float HP;
    float bossHP;
    float overheatcheck;
    sf::Font* font = nullptr;
};
#endif //VIETNAMESE_SPACE_PROGRAM_DYNAMICBAR_H
