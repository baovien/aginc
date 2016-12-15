#ifndef VIETNAMESE_SPACE_PROGRAM_MENU_H
#define VIETNAMESE_SPACE_PROGRAM_MENU_H

#include "../Core/machine.h"
#include "../Core/state.h"
#include "../Core/soundLoader.h"
#include "../Core/utilities.h"

class StateMainMenu : public States{
public:
    void initialize(sf::RenderWindow *window);

    void update(sf::RenderWindow *window);

    void render(sf::RenderWindow *window);

    void destroy(sf::RenderWindow *window);

    void handleEvent(sf::RenderWindow *window , sf::Event event);

    void reinitialize(sf::RenderWindow *window);

private:
    sf::Texture* bgTexture;
    sf::Sprite* background;
    Utilities util;

    struct menuTextureStruct{
        sf::Texture* buttonNormal;
        sf::Texture* buttonMouseOver;
        sf::Texture* buttonClicked;
    };

    menuTextureStruct menuTextures[5];
    sf::Sprite* menuButtons[5];
    sf::Text* title;
};
#endif //VIETNAMESE_SPACE_PROGRAM_MENU_H
