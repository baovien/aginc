#include "../../Include/States/StateSettings.h"
#include "../../Include/States/StateMainMenu.h"
#include "../../Include/States/StateKeybindings.h"

#include <cstring>
#include <iostream>

/**
 * Init settingsState.
 * @param window
 */
void StateSettings::initialize(sf::RenderWindow *window) {

    sf::View newView( sf::FloatRect( 0, 0, window->getSize().x, window->getSize().y ) );
    window->setView(newView);

    memset(machine.keyPressed, 0, sizeof(machine.keyPressed)); //For at tastetrykk gjort i andre states ikke skal beholdes

    this->bgTexture = new sf::Texture();
    this->bgTexture->loadFromFile("Graphics/Sprites/bg_purple.png");


    this->background = new sf::Sprite();
    this->background->setTexture(*this->bgTexture);
    this->background->scale(window->getSize().x/background->getGlobalBounds().width, window->getSize().y/background->getGlobalBounds().height);

    this->selected = 0;

    this->font = new sf::Font();
    this->font->loadFromFile("Graphics/font1.otf");

    this->title = new sf::Text("SETTINGS", *this->font,textSize + 12);
    this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
    this->title->setPosition(window->getSize().x / 2, this->title->getGlobalBounds().height);
    this->title->scale(window->getSize().x/window->getSize().y, window->getSize().x/window->getSize().y);

    this->screenRes = new sf::Text("ScreenRes", *this->font, textSize);
    this->screenRes->setOrigin(this->screenRes->getGlobalBounds().width / 2, this->screenRes->getGlobalBounds().height / 2);
    this->screenRes->setPosition(window->getSize().x / 2, this->screenRes->getGlobalBounds().height*4);

    this->res1 = new sf::Text("1920x1080", *this->font, textSize);
    this->res1->setOrigin(this->res1->getGlobalBounds().width / 2, this->res1->getGlobalBounds().height / 2);
    this->res1->setPosition(window->getSize().x / 4, this->res1->getGlobalBounds().height*6);

    this->res2 = new sf::Text("1280x720", *this->font, textSize);
    this->res2->setOrigin(this->res2->getGlobalBounds().width / 2, this->res2->getGlobalBounds().height / 2);
    this->res2->setPosition(window->getSize().x / 2, this->res2->getGlobalBounds().height*6);

    this->res3 = new sf::Text("640x360", *this->font, textSize);
    this->res3->setOrigin(this->res3->getGlobalBounds().width / 2, this->res3->getGlobalBounds().height / 2);
    this->res3->setPosition(window->getSize().x / 2 +  window->getSize().x / 4, this->res3->getGlobalBounds().height*6);

    this->volume = new sf::Text("Volume", *this->font, textSize);
    this->volume->setOrigin(this->volume->getGlobalBounds().width / 2, this->volume->getGlobalBounds().height / 2);
    this->volume->setPosition(window->getSize().x / 2, this->volume->getGlobalBounds().height*8);

    this->keybinds = new sf::Text("Keybinds", *this->font, textSize);
    this->keybinds->setOrigin(this->keybinds->getGlobalBounds().width / 2, this->volume->getGlobalBounds().height / 2);
    this->keybinds->setPosition(window->getSize().x / 2, this->keybinds->getGlobalBounds().height*10);

    this->apply = new sf::Text("Apply", *this->font, textSize);
    this->apply->setOrigin(this->apply->getGlobalBounds().width / 2, this->apply->getGlobalBounds().height / 2);
    this->apply->setPosition(window->getSize().x / 2, this->apply->getGlobalBounds().height*14);

    this->back = new sf::Text("Back", *this->font, textSize);
    this->back->setOrigin(this->back->getGlobalBounds().width / 2, this->back->getGlobalBounds().height / 2);
    this->back->setPosition(window->getSize().x / 2, this->back->getGlobalBounds().height*16);

}
/**
 * Update on keyevent, navigation through settings
 * @param window
 */
void StateSettings::update(sf::RenderWindow *window) {

    //Vertical selection
    if(machine.keyPressed[sf::Keyboard::Up]){
        memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
        this->selected -= 1;
    }

    if(machine.keyPressed[sf::Keyboard::Down]){
        memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
        this->selected += 1;
    }

    if(this->selected > 4){ //Endre hvis flere alternativer
        this->selected = 0;
    }

    if(this->selected < 0){ //Endre hvis flere alternativer
        this->selected = 4;
    }

    //Horizontal selection resolution

    if(this->selected == 0){
        if(machine.keyPressed[sf::Keyboard::Left]){
            memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
            this->selectedRes -= 1;
        }

        if(machine.keyPressed[sf::Keyboard::Right]){
            memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
            this->selectedRes += 1;
        }

        if(this->selectedRes > 2){ //Endre hvis flere alternativer
            this->selectedRes = 0;
        }

        if(this->selectedRes < 0){ //Endre hvis flere alternativer
            this->selectedRes = 2;
        }
    }

    //Back on escapekey
    if(machine.keyPressed[sf::Keyboard::Escape]){
        memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
        machine.setState(new StateMainMenu);
    }

    //Selection on returnkey

    if(machine.keyPressed[sf::Keyboard::Return]){
        memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
        switch(this->selected){
            case 2:
                machine.setState(new StateKeybindings);
                break;
            case 3: //Apply
                window->setSize(resChoice);
                window->setView(sf::View(sf::FloatRect(0.f, 0.f, window->getSize().x, window->getSize().y)));
                this->initialize(window);
                break;
            case 4: //Back
                machine.setState(new StateMainMenu);
                break;
        }
    }

}
/**
 *
 * @param window
 */
void StateSettings::render(sf::RenderWindow *window) {

    this->screenRes->setStyle(0);
    this->volume->setStyle(0);
    this->keybinds->setStyle(0);
    this->apply->setStyle(0);
    this->back->setStyle(0);

    switch(this->selected){
        case 0: //ScrRes selected, left right to choose res.
            this->res1->setStyle(0);
            this->res2->setStyle(0);
            this->res3->setStyle(0);

            this->screenRes->setStyle(1<<3);

            //Endrer resChoice x og y ved valg
            switch (this->selectedRes){
                case 0:
                    resChoice.x = 1920;
                    resChoice.y = 1080;
                    this->res1->setStyle(1<<3);
                    break;
                case 1:
                    resChoice.x = 1280;
                    resChoice.y = 720;
                    this->res2->setStyle(1<<3);
                    break;
                case 2:
                    resChoice.x = 640;
                    resChoice.y = 360;
                    this->res3->setStyle(1<<3);
                    break;
            }

            break;
        case 1:
            this->volume->setStyle(1<<3);
            break;
        case 2:
            this->keybinds->setStyle(1<<3);
            break;
        case 3:
            this->apply->setStyle(1<<3);
            break;
        case 4:
            this->back->setStyle(1<<3);
            break;

    }


    window->draw(*this->background);
    window->draw(*this->title);
    window->draw(*this->screenRes);
    window->draw(*this->res1);
    window->draw(*this->res2);
    window->draw(*this->res3);
    window->draw(*this->volume);
    window->draw(*this->keybinds);
    window->draw(*this->apply);
    window->draw(*this->back);
}

void StateSettings::destroy(sf::RenderWindow *window) {
    delete this->back;
    delete this->apply;
    delete this->keybinds;
    delete this->font;
    delete this->volume;
    delete this->res3;
    delete this->res2;
    delete this->res1;
    delete this->screenRes;
    delete this->title;
    delete this->background;
}
