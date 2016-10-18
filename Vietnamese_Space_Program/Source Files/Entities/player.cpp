#include "../../Header Files/Entities/playerobject.h"
playerObject::playerObject(int playerNumber)
{
    this->playerNumber  = playerNumber;
    switch(this->playerNumber)
    {
        case 0:
            this->Load("ball.png");
            break;
        default:
            break;
    }
}

void playerObject::Update()
{
    bool up, down, left, right;
    switch(this->playerNumber) {
        case 0:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))left=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))right=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))up=1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))down=1;

            //Bevegelse
            if (up && speed < maxSpeed)
                if (speed < 0) speed += dec;
                else speed += acc;

            if (down && speed >-maxSpeed)
                if (speed > 0) speed -= dec;
                else speed -= acc;
            if (!up && !down)
                if (speed - dec > 0) speed -= dec;
                else if (speed + dec < 0) speed += dec;
                else speed = 0;

            if (right && speed != 0) angle += turnspeed * speed/maxSpeed;
            if (left && speed != 0) angle -= turnspeed * speed/maxSpeed;
        default:
            break;

    }
    Entity::Update();
    if(this->getPosition().y < 0)
    {
        this->move(0, 1.0f);
    }
    if(this->getPosition().y + this->getGlobalBounds().height > 1080)
    {
        this->move(0, -1.0f);
    }
    if(this->getPosition().x < 0)
    {
        this->move(1.0f, 0);
    }
    if(this->getPosition().x + this->getGlobalBounds().height > 1920)
    {
        this->move(-1.0f, 0);
    }
}