#include <SFML/Graphics.hpp>
#ifndef VIETNAMESE_SPACE_PROGRAM_BULLET_ENTITY_H
#define VIETNAMESE_SPACE_PROGRAM_BULLET_ENTITY_H

class bullet_entity : public sf::Sprite
{
public:
    sf::Vector2f movement;
    bullet_entity()
    {
        this->texture = new sf::Texture();
    }
    void Load(std::string filename)
    {
        this->texture->loadFromFile("Graphics/Sprites/" + filename);
        this->setTexture(*this->texture);
    }
    virtual void Update()
    {
        this->move(this->movement);
    }

    bool checkCollision(bullet_entity* entity)
    {
        return this->getGlobalBounds().intersects(entity->getGlobalBounds());
    }
    ~bullet_entity()
    {
        delete this->texture;
    }

protected:

private:
    sf::Texture* texture;
};
#endif //VIETNAMESE_SPACE_PROGRAM_BULLET_ENTITY_H
