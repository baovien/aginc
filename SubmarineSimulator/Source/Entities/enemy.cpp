
#include <iostream>
#include "../../Include/Entities/enemy.h"


/**
 * Game mode 1's enemy's constructor.
 * @param window
 * @param player
 * @param manager - The entitymanager
 * @param mode - Current wave. Deciding whether the enemy shoots or not.
 * @param audioLoader
 * @param theme - Current theme, deciding what texture to load.
 * @return
 */
EnemyObject::EnemyObject(sf::RenderWindow* window, Player* player, EntityManager* manager, int wave, AudioLoader* audioLoader, int theme)
            : player(player),
              manager(manager),
              audioLoader(audioLoader),
              mode(wave),
              theme(theme)
{
    if(theme == 0)this->load("happyfish.png");
    else this->load("UFO3.png");

    this->active = 1;
    this->groupId = 4;
    this->randomNumber = rand() % 4;
    this->easingAmount = 0.05f;
    this->maxSpeed = 100.0f + mode;
    this->setOrigin(this->getGlobalBounds().height/2.f, this->getGlobalBounds().height/2.f);
    this->setScale(window->getSize().x/2560.0f, window->getSize().y/1440.0f);
    if(this->mode > 5) this->health = 3;
    else this->health = 2;
    //Spawner enemy utenfor vinduet
    if (randomNumber == 1) {
        this->setPosition(0 - this->getGlobalBounds().width * 2, rand() % window->getSize().y);
    } else if (randomNumber == 2) {
        this->setPosition(window->getSize().x + this->getGlobalBounds().width * 2.f, rand() % window->getSize().y);
    } else if (randomNumber == 3) {
        this->setPosition(rand() % window->getSize().x + this->getGlobalBounds().width* 2, 0 - this->getGlobalBounds().height * 2);
    } else {
        this->setPosition(rand() % window->getSize().x + this->getGlobalBounds().width * 2, window->getSize().y + this->getGlobalBounds().height * 2);
    }

}

/**
 * Controls the enemy's position, bullet firing and needed texture, given by it's hp.
 * @param window
 */
void EnemyObject::updateEntity(sf::RenderWindow *window) {
    this->xDistance = this->player->getPosition().x - this->getPosition().x;
    this->yDistance = this->player->getPosition().y - this->getPosition().y;
    this->distance = sqrtf((this->xDistance * this->xDistance) + (this->yDistance * this->yDistance));
    double alpha = sin(yDistance/distance);
    alpha = alpha * 180/player->pi;


    if (this->distance > 1) {
        this->velocity.x += this->xDistance * this->easingAmount;
        this->velocity.y += this->yDistance * this->easingAmount;

        if (this->velocity.x > maxSpeed) {
            this->velocity.x = maxSpeed;
        }
        if (this->velocity.y > maxSpeed) {
            this->velocity.y = maxSpeed;
        }
        if (this->velocity.x < -maxSpeed) {
            this->velocity.x = -maxSpeed;
        }
        if (this->velocity.y < -maxSpeed) {
            this->velocity.y = -maxSpeed;
        }
    }
    int randomNumber2;
    randomNumber2 = rand() % 1000;
    if(this->mode > 5 && randomNumber2 < 2)
    {
        //float angle = this->getRotation() * player->pi/180;
        this->manager->addEntity("bullet", new Bullet(this->getPosition().x /*+ (this->getGlobalBounds().width/2) * sin(angle)*/,
                                                      this->getPosition().y /*- (this->getGlobalBounds().height/2) * cos(angle)*/,
                                                      yDistance/900.f,
                                                      xDistance/900.f,
                                                      0,
                                                      window, theme));
        this->audioLoader->playEffect(Audio::ENEMY_SHOOT);
    }
    //Sjekker om spilleren er til venstre for fienden.
    if(player->getPosition().x < this->getPosition().x){
        float turn = window->getSize().x/2560.f;
        turn *= -1;
        this->setScale(turn, this->getScale().y);
        //Sjekker om spilleren er over fienden
        if(player->getPosition().y < this->getPosition().y){
            this->setRotation(-alpha);
        }
        //Sjekker om spilleren er under fisken
        else if(player->getPosition().y > this->getPosition().y){
            this->setRotation(-alpha);
        }
    }
    //Hvis spilleren ikke er til venstre for fienden, da er den til høyre.
    else {
        this->setScale(window->getSize().x/2560.f, this->getScale().y);
        //Sjekker om spilleren er over fienden.
        if(player->getPosition().y < this->getPosition().y){
           this->setRotation(alpha);
        }
        //Sjekker om spilleren er under fienden.
        else if(player->getPosition().y > this->getPosition().y) {
            this->setRotation(alpha);
        }
    }
    if(this->health == 1){
        if(theme == 0){
            this->load("dizzyfish.png");
        }
        else{
            this->load("UFO1.png");
        }

    }
    else if(this->health <= 0){
        if(theme == 0){
            this->load("deadfish.png");
            this->destroyEntity();
        }
        else{
            this->load("UFO2.png");
            this->destroyEntity();
        }

    }
    if(player->getPosition().y < this->getPosition().y){

    }
    Entity::updateEntity(window);
}

/**
 * Decides the outcome of a collision between the player and the given entity.
 * @param entity - entity being checked for collision.
 */
void EnemyObject::collision(Entity *entity) {
    switch (entity->groupID()) {
        case 2: // Player sine kuler.
            this->health--;
            break;

        case 4: //Andre fiender, vil ikke at de skal overlappes.
            this->velocity.x *= -1;
            this->velocity.y *= -1;
            entity->velocity.x = this->velocity.x * -1;
            entity->velocity.y = this->velocity.y * -1;
            break;

        default:break;
    }
}