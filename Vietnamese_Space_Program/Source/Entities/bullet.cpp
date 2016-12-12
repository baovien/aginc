#include "../../Include/Entities/bullet.h"
#include <iostream>

Bullet::Bullet(Score* score, float x, float y, float direction, float direction2, float angle, SoundLoader* soundLoader, sf::RenderWindow* window, int fighter)
        : soundLoader(soundLoader)
{
    this->fighter = fighter;
    this->active = 1;
    this->groupId = 2;
    if(fighter==0){
        this->load("missile.png");
        this->setScale(window->getSize().x/3840.0f, window->getSize().y/2160.0f);
    }
    else{
        this->load("laser.png");
        this->setScale(window->getSize().x/1280.0f, window->getSize().y/720.0f);
    }

    this->velocity.y = direction * 640;
    this->velocity.x = direction2 * 640;
    this->setOrigin(this->getGlobalBounds().width/2.f, this->getGlobalBounds().height/2.f);
    this->setPosition(x, y);
    this->setRotation(angle);
    this->score = score;


}
Bullet::Bullet(float x, float y, float direction, float direction2, float angle , sf::RenderWindow* window, int theme)
{
    this->active = 1;
    this->theme = theme;
    this->groupId = 6;
    if(theme == 0)this->load("bubble4.png");
    else this->load("bulllet.png");
    this->velocity.y = direction * 640;
    this->velocity.x = direction2 * 640;
    this->setOrigin(this->getGlobalBounds().width/2.f, this->getGlobalBounds().height/2.f);
    this->setPosition(x, y);
    this->setRotation(angle);
    this->setScale(window->getSize().x/2560.0f, window->getSize().y/1440.0f);
}
void Bullet::updateEntity(sf::RenderWindow *window)
{
    if(this->getPosition().x + this->getGlobalBounds().width/2.f < 0 || this->getPosition().x - this->getGlobalBounds().width/2.f > window->getSize().x||
       this->getPosition().y + this->getGlobalBounds().height/2.f < 0 || this->getPosition().y - this->getGlobalBounds().height/2.f > window->getSize().y)
    {
        this->destroyEntity();
    }
    Entity::updateEntity(window);
}

void Bullet::collision(Entity *entity)
{
    if(this->groupId == 2)
    {

        switch (entity->groupID())
        {
            case 3: // IndestructableObject nr 1
                this->destroyEntity();
                this->soundLoader->playEffect(Audio::BULLET_POP);
                break;

            case 4: // Enemy
                this->destroyEntity();
                this->score->incrementScore();
                this->soundLoader->playEffect(Audio::BULLET_POP);
                break;

            case 5: // Boss
                this->destroyEntity();
                this->score->incrementScore();
                this->soundLoader->playEffect(Audio::BULLET_POP);
                break;

            case 9: // IndestructableObject nr 2
                this->destroyEntity();
                this->soundLoader->playEffect(Audio::BULLET_POP);
                break;

            default:
                break;
        }
    }
}

