#include <iostream>
#include <cstring>
#include "../../Include/States/stateMainMenu.h"
#include "../../Include/States/stateHighscore.h"
#include "../../Include/States/statePlayConfig.h"
#include "../../Include/States/stateSettings.h"
#include "../../Include/States/stateHelp.h"
#include "../../Include/States/stateGameOver.h"


void StateMainMenu::initialize(sf::RenderWindow *window) {
    machine.audioLoaderPointer->playMusic(Audio::MAIN_MENU);

    sf::View newView(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    window->setView(newView);

    this->bgTexture = new sf::Texture();
    this->bgTexture->loadFromFile("Graphics/Sprites/bakgrunn.png");

    this->background = new sf::Sprite();
    this->background->setTexture(*this->bgTexture);
    this->background->scale(window->getSize().x / background->getGlobalBounds().width, window->getSize().y / background->getGlobalBounds().height);

    //loader alle knapper og versjoner av knapper. Finnes 3 versjoner av hver (vanlig, mouseover og clicked).
    //Ganger med 3 fordi jeg kun vil få hver 3. knapp
    for (unsigned int i = 0; i < (sizeof(menuTextures) / sizeof(*menuTextures)); ++i)
    {
        menuTextures[i].buttonMouseOver = new sf::Texture();
        menuTextures[i].buttonMouseOver->loadFromFile("Graphics/Sprites/MainMenu_buttons/Btn" + std::to_string(i * 3) + ".png");

        menuTextures[i].buttonNormal = new sf::Texture();
        menuTextures[i].buttonNormal->loadFromFile("Graphics/Sprites/MainMenu_buttons/Btn" + std::to_string(i * 3 + 1) + ".png");

        menuTextures[i].buttonClicked = new sf::Texture();
        menuTextures[i].buttonClicked->loadFromFile("Graphics/Sprites/MainMenu_buttons/Btn" + std::to_string(i * 3 + 2) + ".png");

        menuButtons[i] = new sf::Sprite();
        menuButtons[i]->setTexture(*this->menuTextures[i].buttonNormal);
        menuButtons[i]->setOrigin(menuButtons[i]->getGlobalBounds().width / 2, menuButtons[i]->getGlobalBounds().height / 2);
        if(i<5 && i>0) {
            menuButtons[i]->scale(window->getSize().x/1920.f,  window->getSize().y/1080.f);
        }
        menuButtons[i]->setPosition(i * window->getSize().x / 5, window->getSize().y - window->getSize().y / 4);
    }
    //Scaler og posisjoner de som varierer mye ift. de andre utenfor for-løkken
    menuButtons[0]->scale(window->getSize().x/960.f,  window->getSize().y/540.f);
    menuButtons[0]->setPosition(window->getSize().x / 2, window->getSize().y / 2.5f);

    util.makeMuteButton(window, machine.mutedPointer);

    //Text, textsize, origin x, origin y, position x, position y
    title = util.addText("Submarine Simulator", 100, 2, 2, menuButtons[0]->getPosition().x, window->getSize().y/15.f, window, machine.settingPointer->selectedLanguage);
}

void StateMainMenu::update(sf::RenderWindow *window) {
    //Sjekker mutemusic er satt
    machine.audioLoaderPointer->updateSounds();

    //Sjekker mouseover for hver knapp og endrer texture om den er mouseovera eller trykket
    util.checkMuteMouseOver(window);
    for (unsigned int i = 0; i < (sizeof(menuTextures) / sizeof(*menuTextures)); ++i) {
        if (util.checkMouseover(menuButtons[i], window)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                menuButtons[i]->setTexture(*this->menuTextures[i].buttonClicked);
            } else {
                menuButtons[i]->setTexture(*this->menuTextures[i].buttonMouseOver);
            }
        } else {
            menuButtons[i]->setTexture(*this->menuTextures[i].buttonNormal);
        }
    }

}

void StateMainMenu::render(sf::RenderWindow *window) {
    window->draw(*this->background);
    window->draw(*this->title);

    for (unsigned int i = 0; i < (sizeof(menuTextures) / sizeof(*menuTextures)); ++i) {
        window->draw(*this->menuButtons[i]);
    }
    window->draw(*util.getMuteButton());

}

void StateMainMenu::destroy(sf::RenderWindow *window) {

    //Destroyer i motsatt rekkefølge av draws
    for (int i = (sizeof(menuTextures) / sizeof(*menuTextures)) - 1; i >= 0; --i) {
        delete this->menuButtons[i];
        delete this->menuTextures[i].buttonMouseOver;
        delete this->menuTextures[i].buttonClicked;
        delete this->menuTextures[i].buttonNormal;
    }
    delete this->title;
    delete this->background;
    delete this->bgTexture;

}

void StateMainMenu::handleEvent(sf::RenderWindow *window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased) {

        util.checkMuteMouseClick(window, event, machine.mutedPointer);

        for (unsigned int i = 0; i < (sizeof(menuTextures) / sizeof(*menuTextures)); ++i)
            if (util.checkMouseclick(menuButtons[i], event)) {
                switch (i) {
                    //playknappen trykket
                    case 0:
                        machine.setState(new StatePlayConfig());
                        return;
                        //highscoreknappen trykket
                    case 1:
                        machine.setState(new StateHighscore());
                        return;
                        //settingsknappen trykket
                    case 2:
                        machine.setState(new StateSettings());
                        return;
                        //helpknappen trykket
                    case 3:
                        machine.setState(new stateHelp());
                        return;
                        //exitknappen trykket
                    case 4:
                        quitGame = true;
                        return;
                    default:break;
                }
            }
    }
}

void StateMainMenu::reinitialize(sf::RenderWindow *window) {
    destroy(window);
    initialize(window);
}

